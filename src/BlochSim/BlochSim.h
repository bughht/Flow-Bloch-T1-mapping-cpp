#ifndef BLOCHSIM_H
#define BLOCHSIM_H

#include <Eigen/Dense>
#include <cmath>

using Eigen::Matrix3d;
using Eigen::Vector3d;

struct FP_args
{
    Matrix3d A;
    Vector3d B;
};

Matrix3d Rz(double theta);
Matrix3d Ry(double theta);
Matrix3d Rx(double theta);

FP_args freeprecess(double T, double T1, double T2, double df);

#endif