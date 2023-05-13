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
    vector<int> ksize;

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
        vector<int> ksize,
        int n_particle);

    void vessel_init(void);
    void particle_init(void);
    void show(void);

    void free_precess(double t, double Gx, double Gy, double Gz);
    void flow(double t);
    void flip(double FA, double thickness);
    void update_outofrange(vector<TS> &flip_global, double t_now);

    complex<double> adc();
};

#endif