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

#include <BlochSim.h>
#include <iostream>
#include <Eigen/Dense>

using Eigen::Matrix3d;
using Eigen::Vector3d;

int main()
{
  Vector3d m;
  m << 0, 0, 0;
  for (int i = 0; i < 100; i++)
  {
    FP_args args = freeprecess(10, 1000, 100, 0);
    m = args.A * m + args.B;
    std::cout << "m =" << std::endl
              << m << std::endl;
  }
}