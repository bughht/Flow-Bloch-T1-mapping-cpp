// Copyright (C) 2023 Haotian Hong
//
// This file is part of FLOW-BLOCH-T1-MAPPING-CPP.
//
// FLOW-BLOCH-T1-MAPPING-CPP is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// FLOW-BLOCH-T1-MAPPING-CPP is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FLOW-BLOCH-T1-MAPPING-CPP.  If not, see <http://www.gnu.org/licenses/>.

#include "FlowPhantom.h"

#define PARALLEL_THREAD 32

FlowPhantom::FlowPhantom(
    int n_vessel_x,
    int n_vessel_y,
    double vessel_radius,
    vector<double> T1,
    vector<double> T2,
    vector<double> flow_speed,
    vector<double> space,
    vector<int> ksize,
    int n_particle)
{
    this->n_vessel_x = n_vessel_x;
    this->n_vessel_y = n_vessel_y;
    this->vessel_radius = vessel_radius;
    this->T1 = T1;
    this->T2 = T2;
    this->flow_speed = flow_speed;
    this->space = space;
    this->ksize = ksize;
    this->n_particle = n_particle;

    this->vessel_init();
    this->particle_init();
}

void FlowPhantom::vessel_init(void)
{
    this->n_vessel = this->n_vessel_x * this->n_vessel_y;
    for (int x = 0; x < this->n_vessel_x; x++)
        for (int y = 0; y < this->n_vessel_y; y++)
        {
            Vector2d center;
            center << this->space[0] * (2 * x + 1 - this->n_vessel_x) / (2 * this->n_vessel_x), this->space[1] * (2 * y + 1 - this->n_vessel_y) / (2 * this->n_vessel_y);
            this->vessel_centers.push_back(center);
        }
}

void FlowPhantom::particle_init(void)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    // std::uniform_int_distribution<int> distribution_kx(-this->ksize[0] / 2 + 1, this->ksize[0] / 2 - 1);
    // std::uniform_int_distribution<int> distribution_ky(-this->ksize[1] / 2, this->ksize[1] / 2 - 1);
    std::uniform_real_distribution<double> distribution_x(-this->space[0] / 2, this->space[0] / 2);
    std::uniform_real_distribution<double> distribution_y(-this->space[1] / 2, this->space[1] / 2);
    std::uniform_real_distribution<double> distribution_z(-this->space[2] / 2, this->space[2] / 2);

    for (int i = 0; i < this->n_particle; i++)
    {
        Vector3d position(
            // 1.0 * distribution_kx(gen) / this->ksize[0] * this->space[0], 1.0 * distribution_ky(gen) / this->ksize[1] * this->space[1], distribution_z(gen));
            distribution_x(gen), distribution_y(gen), distribution_z(gen));
        double p_T1 = this->T1.back();
        double p_T2 = this->T2.back();
        double p_flow_speed = 0;
        for (int j = 0; j < this->n_vessel; j++)
        {
            if ((position.head<2>() - this->vessel_centers[j]).norm() < this->vessel_radius)
            {
                // std::cout << position[0] << " " << position[1] << " " << (position.head<2>() - this->vessel_centers[j]).norm() << " ";
                p_T1 = this->T1[j];
                p_T2 = this->T2[j];
                p_flow_speed = this->flow_speed[j];
                break;
            }
        }
        // std::cout << p_T1 << std::endl;
        M_voxel particle(
            p_T1,
            p_T2,
            position,
            Vector3d(0, 0, 1),
            Vector3d(0, 0, p_flow_speed));
        this->particles.push_back(particle);
    }
}

void FlowPhantom::show(void)
{
    for (M_voxel &particle : this->particles)
    {
        std::cout << "POS: [" << particle.pos[0] << " " << particle.pos[1] << " " << particle.pos[2] << "]" << std::endl;
        std::cout << "T1/T2/Flowspeed: " << particle.T1 << "/" << particle.T2 << "/" << particle.flow_speed[2] << std::endl;
        std::cout << "M: [" << particle.M[0] << " " << particle.M[1] << " " << particle.M[2] << "]" << std::endl;
    }
}

void FlowPhantom::free_precess(double t, double Gx, double Gy)
{
#pragma omp parallel for num_threads(PARALLEL_THREAD)
    for (M_voxel &particle : this->particles)
        particle.free_precess(t, Gx, Gy);
}

void FlowPhantom::flow(double t)
{
#pragma omp parallel for num_threads(PARALLEL_THREAD)
    for (M_voxel &particle : this->particles)
        particle.update_pos(t);
}

void FlowPhantom::flip(double FA, double thickness)
{
    if (thickness == 0)
#pragma omp parallel for num_threads(PARALLEL_THREAD)
        for (M_voxel &particle : this->particles)
        {
            particle.flip(FA);
        }
    else
    {
#pragma omp parallel for num_threads(PARALLEL_THREAD)
        for (M_voxel &particle : this->particles)
        {
            if (fabs(particle.pos[2]) < thickness / 2)
                particle.flip(FA);
        }
    }
}

void FlowPhantom::update_outofrange(vector<TS> &flip_global, double t_now)
{
#pragma omp parallel for num_threads(PARALLEL_THREAD)
    for (M_voxel &particle : this->particles)
    {
        if (particle.pos[2] > this->space[2] / 2)
        {
            double t_particle = 0;
            while (particle.pos[2] > this->space[2] / 2)
                particle.pos[2] -= this->space[2];
            particle.M = Vector3d(0, 0, 1);
            for (TS &flip : flip_global)
            {
                particle.free_precess(flip.t - t_particle, 0, 0);
                particle.flip(flip.FA);
                t_particle = flip.t;
            }
            particle.free_precess(t_now - t_particle, 0, 0);
        }
    }
}

complex<double> FlowPhantom::adc()
{
    // complex<double> sum(0, 0);
    double sum_r = 0, sum_i = 0;

// #pragma omp parallel for num_threads(32) shared(sum)
#pragma omp parallel for reduction(+ : sum_i) reduction(+ : sum_r) num_threads(32)
    for (M_voxel &particle : this->particles)
    {
        // #pragma omp atomic
        // sum += particle.adc();
        sum_r += particle.adc().real();
        sum_i += particle.adc().imag();
    }
    // return sum * (1.0 / this->n_particle);
    return complex<double>(sum_r, sum_i);
    // return sum;
}
