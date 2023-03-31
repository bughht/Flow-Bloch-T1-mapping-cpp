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
}

FlowPhantom::~FlowPhantom()
{
}

void FlowPhantom::vessel_init(void)
{
    this->n_vessel = this->n_vessel_x * this->n_vessel_y;
    for (int x = 0; x < this->n_vessel_x; x++)
        for (int y = 0; y < this->n_vessel_y; y++)
        {
            Vector2d center;
            center << this->space[0] / (this->n_vessel_x + 1) * x << this->space[1] / (this->n_vessel_y + 1) * y;
            this->vessel_centers.push_back(center);
        }
}