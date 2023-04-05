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

#include "BlochSim.h"

Matrix3d Rz(double theta)
{
    Matrix3d Rz;
    Rz << cos(theta), -sin(theta), 0,
        sin(theta), cos(theta), 0,
        0, 0, 1;
    return Rz;
}

Matrix3d Ry(double theta)
{
    Matrix3d Ry;
    Ry << cos(theta), 0, sin(theta),
        0, 1, 0,
        -sin(theta), 0, cos(theta);
    return Ry;
}

Matrix3d Rx(double theta)
{
    Matrix3d Rx;
    Rx << 1, 0, 0,
        0, cos(theta), -sin(theta),
        0, sin(theta), cos(theta);
    return Rx;
}

FP_args freeprecess(double T, double T1, double T2, double df)
{
    FP_args args;
    double phi = 2 * M_PI * df * T / 1000;
    double E1 = exp(-T / T1);
    double E2 = exp(-T / T2);
    args.A << E2, 0, 0,
        0, E2, 0,
        0, 0, E1;
    args.A = args.A * Rz(phi);
    args.B << 0, 0, (1 - E1);
    return args;
}