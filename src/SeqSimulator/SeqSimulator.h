#ifndef SEQSIMULATOR_H
#define SEQSIMULATOR_H

#include <Eigen/Dense>
#include <eigen3/unsupported/Eigen/FFT>
#include <BlochSim.h>
#include <M_voxel.h>
#include <SeqLoader.h>
#include <matplotlibcpp.h>

using Eigen::MatrixXcd;
using std::vector;
void simulate_single(vector<TS> seq, M_voxel m, vector<int> k_shape);

#endif