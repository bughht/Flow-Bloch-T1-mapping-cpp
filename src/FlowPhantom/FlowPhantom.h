#ifndef FLOWPHANTOM_H
#define FLOWPHANTOM_H

#include <Eigen/Dense>
#include <M_voxel.h>
#include <SeqLoader.h>
#include <cmath>
#include <random>
#include <complex>
#include <omp.h>
#include <iostream>

using Eigen::Matrix3d;
using Eigen::Vector2d;
using Eigen::Vector3d;
using std::complex;
using std::vector;

class FlowPhantom
{
public:
    int n_vessel_x;
    int n_vessel_y;
    int n_vessel;
    int vessel_radius;
    vector<Vector2d> vessel_centers;

    vector<double> T1;
    vector<double> T2;
    vector<double> flow_speed;

    vector<double> space;

    vector<M_voxel> particles;
    int n_particle;

    FlowPhantom(
        int n_vessel_x,
        int n_vessel_y,
        double vessel_radius,
        vector<double> T1,
        vector<double> T2,
        vector<double> flow_speed,
        vector<double> space,
        int n_particle);

    void vessel_init(void);
    void particle_init(void);
    void show(void);

    void free_precess(double t, double Gx, double Gy);
    void flow(double t);
    void flip(double FA, double thickness);
    void update_outofrange(vector<TS> &flip_global, double t_now);

    complex<double> adc();
};

#endif