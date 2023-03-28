#ifndef SEQSIMULATOR_H
#define SEQSIMULATOR_H

#include <filesystem>
#include <Eigen/Dense>
#include <BlochSim.h>
#include <M_voxel.h>
#include <SeqLoader.h>
#include <matplotlibcpp.h>
#include <opencv2/core/eigen.hpp>
#include <opencv2/opencv.hpp>

using Eigen::MatrixXcd;
using std::string;
using std::vector;

namespace fs = std::filesystem;
namespace plt = matplotlibcpp;

void simulate_single(vector<TS> seq, M_voxel m, vector<int> k_shape);
void simulate_plane(vector<TS> seq, vector<M_voxel> m_plane, vector<int> k_shape);
void simulate_volume(vector<TS> seq, vector<M_voxel> m_voxels, vector<int> kshape, fs::path save_path);

#endif