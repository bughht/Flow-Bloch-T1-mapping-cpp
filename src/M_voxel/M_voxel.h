#ifndef M_VOXEL_H
#define M_VOXEL_H

#include <Eigen/Dense>
#include <cmath>
#include <complex>
#include <BlochSim.h>

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
    ADC_args();
    ADC_args(Vector3d M);
    ADC_args(double Mx, double My, double Mz);
};

class M_voxel
{
private:
    double T1;
    double T2;
    Vector3d pos;
    Vector3d M;

public:
    M_voxel(double T1, double T2, Vector3d pos, Vector3d M);
    ~M_voxel();
    void flip(double FA);
    void free_precess(double T, double Gx, double Gy);
    ADC_args readout();
};

#endif