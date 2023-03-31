#include "FlowPhantom.h"

FlowPhantom::FlowPhantom(
    int n_vessel_x,
    int n_vessel_y,
    double vessel_radius,
    vector<double> T1,
    vector<double> T2,
    vector<double> flow_speed,
    vector<double> space,
    int n_particle)
{
    this->n_vessel_x = n_vessel_x;
    this->n_vessel_y = n_vessel_y;
    this->vessel_radius = vessel_radius;
    this->T1 = T1;
    this->T2 = T2;
    this->flow_speed = flow_speed;
    this->space = space;
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
            center << this->space[0] / (this->n_vessel_x + 1) * (x + 1) - this->space[0] / 2, this->space[1] / (this->n_vessel_y + 1) * (y + 1) - this->space[1] / 2;
            this->vessel_centers.push_back(center);
        }
}

void FlowPhantom::particle_init(void)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution_x(-this->space[0] / 2, this->space[0] / 2);
    std::uniform_real_distribution<double> distribution_y(-this->space[1] / 2, this->space[1] / 2);
    std::uniform_real_distribution<double> distribution_z(-this->space[2] / 2, this->space[2] / 2);

    for (int i = 0; i < this->n_particle; i++)
    {
        Vector3d position(
            distribution_x(gen), distribution_y(gen), distribution_z(gen));
        double p_T1 = this->T1.back();
        double p_T2 = this->T2.back();
        double p_flow_speed = 0;
        for (int j = 0; j < this->n_vessel; j++)
        {
            if ((position.head<2>() - this->vessel_centers[j]).norm() < this->vessel_radius)
            {
                p_T1 = this->T1[j];
                p_T2 = this->T2[j];
                p_flow_speed = this->flow_speed[j];
            }
        }
        M_voxel particle(
            p_T1,
            p_T2,
            position,
            Vector3d(0, 0, 1),
            Vector3d(0, 0, p_flow_speed));
        this->particles.push_back(particle);
    }
}

void FlowPhantom::free_precess(double t, double Gx, double Gy)
{
#pragma omp parallel for num_threads(64)
    for (M_voxel &particle : this->particles)
        particle.free_precess(t, Gx, Gy);
}

void FlowPhantom::flow(double t)
{
#pragma omp parallel for num_threads(64)
    for (M_voxel &particle : this->particles)
        particle.update_pos(t);
}

void FlowPhantom::flip(double FA, double thickness)
{
    if (thickness == -1)
#pragma omp parallel for num_threads(64)
        for (M_voxel &particle : this->particles)
        {
            particle.flip(FA);
        }
    else
    {
#pragma omp parallel for num_threads(64)
        for (M_voxel &particle : this->particles)
        {
            if (fabs(particle.pos[2]) < thickness / 2)
                particle.flip(FA);
        }
    }
}