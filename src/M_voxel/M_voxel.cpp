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

#include "M_voxel.h"

ADC_args::ADC_args(Vector3d M)
{
    this->M = M;
    this->Mz = M(2);
    this->Mxy = {M(0), M(1)};
    this->amplitude = abs(Mxy);
    this->phase = arg(Mxy);
}

ADC_args::ADC_args(double Mx, double My, double Mz)
{
    this->M << Mx, My, Mz;
    this->Mz = Mz;
    this->Mxy = {Mx, My};
    this->amplitude = abs(Mxy);
    this->phase = arg(Mxy);
}

M_voxel::M_voxel(double T1, double T2, Vector3d pos = Vector3d(0, 0, 0), Vector3d M = Vector3d(0, 0, 1), Vector3d flow_speed = Vector3d(0, 0, 0))
{
    this->T1 = T1;
    this->T2 = T2;
    this->pos = pos;
    this->M = M;
    this->flow_speed = flow_speed;
}

M_voxel::~M_voxel()
{
}

void M_voxel::flip(double FA)
{
    double theta = FA * M_PI / 180;
    Matrix3d R = Ry(theta);
    // std::cout << "origin" << this->M.transpose() << std::endl;
    this->M = R * this->M;
    // std::cout << "flipped" << this->M.transpose() << std::endl;
}

void M_voxel::free_precess(double T, double Gx, double Gy)
{
    // std::cout << "Gx: " << Gx << ", Gy: " << Gy << ", t: " << T << std::endl;
    double df = GAMMA * Gx * this->pos(0) + GAMMA * Gy * this->pos(1);
    FP_args AB = freeprecess(T, this->T1, this->T2, df);
    this->M = AB.A * this->M + AB.B;
}

void M_voxel::update_pos(double dt)
{
    this->pos += this->flow_speed * dt;
}

Vector3d M_voxel::get_pos()
{
    return this->pos;
}

ADC_args M_voxel::readout()
{
    ADC_args adc(this->M);
    return adc;
}

complex<double> M_voxel::adc()
{
    return {this->M(0), this->M(1)};
}