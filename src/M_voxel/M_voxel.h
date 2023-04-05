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