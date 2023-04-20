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

#ifndef BLOCHSIM_H
#define BLOCHSIM_H

#include <Eigen/Dense>
// #include <torch/torch.h>
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