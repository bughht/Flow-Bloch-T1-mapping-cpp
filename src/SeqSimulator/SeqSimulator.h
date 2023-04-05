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

#ifndef SEQSIMULATOR_H
#define SEQSIMULATOR_H

#include <filesystem>
#include <Eigen/Dense>
#include <BlochSim.h>
#include <M_voxel.h>
#include <FlowPhantom.h>
#include <SeqLoader.h>
#include <omp.h>
// #include <matplotlibcpp.h>
#include <opencv2/core/eigen.hpp>
#include <opencv2/opencv.hpp>

using Eigen::MatrixXcd;
using std::string;
using std::vector;

namespace fs = std::filesystem;
// namespace plt = matplotlibcpp;

void simulate_single(vector<TS> seq, M_voxel m, vector<int> k_shape);
void simulate_plane(vector<TS> seq, vector<M_voxel> m_plane, vector<int> k_shape);
void simulate_volume(vector<TS> seq, vector<M_voxel> m_voxels, vector<int> kshape, fs::path save_path);
void simulate_phantom(vector<TS> seq, FlowPhantom phantom, vector<int> k_shape, fs::path save_path);

#endif