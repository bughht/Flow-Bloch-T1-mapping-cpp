#ifndef M_VOXEL_H
#define M_VOXEL_H

#include <iostream>
#include <Eigen/Dense>
#include <cmath>
#include <complex>
#include <BlochSim.h>

const double GAMMA = 42577478.518;

using Eigen::Matrix3d;
using Eigen::Vector3d;
using std::complex;

struct ADC_args
{
    Vector3d M;
    double Mz;
    complex<double> Mxy;
    double amplitude;
    double phase;
    ADC_args(Vector3d M);
    ADC_args(double Mx, double My, double Mz);
};

class M_voxel
{
public:
    double T1;
    double T2;
    Vector3d pos;
    Vector3d M;
    Vector3d flow_speed;

    // M_voxel(double T1, double T2, Vector3d pos, Vector3d M, Vector3d speed);
    M_voxel(double T1, double T2, Vector3d pos, Vector3d M, Vector3d flow_speed);
    ~M_voxel();
    void flip(double FA);
    void free_precess(double T, double Gx, double Gy);
    void update_pos(double dt);
    Vector3d get_pos();
    ADC_args readout();
    complex<double> adc();
};

#endif