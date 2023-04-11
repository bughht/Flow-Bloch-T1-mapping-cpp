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

#include <cmath>
#include <cassert>
#include <iostream>
#include <BlochSim.h>
#include <Eigen/Dense>
#include <M_voxel.h>
#include <iostream>
#include <SeqSimulator.h>
#include "argparse.hpp"
// #include <matplotlibcpp.h>

using Eigen::Matrix;
using Eigen::Matrix3d;
using Eigen::Vector3d;
using std::vector;

int main(int argc, char **argv)
{
    argparse::ArgumentParser program("test_FlowPhantom");
    program.add_argument("-seq", "--seq_path")
        .help("sequence path")
        .default_value(string("sequences_MOLLI/MOLLI_533_TR2.8_FA35_FOV256_K64_thick8_center_first.yaml"));
    program.add_argument("-s", "--save_path")
        .help("save path")
        .default_value(string("img_MOLLI/Phantom_MOLLI_533_TR2.8_FA35_FOV256_K64_thick8_center_first"));
    program.add_argument("-n", "--n_vessel_xy")
        .help("number of vessels in x and y direction")
        .nargs(2)
        .default_value(vector<int>{2, 2})
        .scan<'d', int>();
    program.add_argument("-r", "--vessel_radius")
        .help("radius of vessel")
        .default_value(60.)
        .scan<'g', double>();
    program.add_argument("-N", "--n_particle")
        .help("number of particles")
        .default_value(5000000)
        .scan<'d', int>();
    program.add_argument("--T1_Blood")
        .help("T1 of blood")
        .default_value(vector<double>{1500., 1500., 1500., 1500.})
        .nargs(argparse::nargs_pattern::any)
        .scan<'g', double>();
    program.add_argument("--T2_Blood")
        .help("T2 of blood")
        .default_value(vector<double>{200., 200, 200, 200})
        .nargs(argparse::nargs_pattern::any)
        .scan<'g', double>();
    program.add_argument("--T1_Tissue")
        .help("T1 of tissue")
        .default_value(500.)
        .scan<'g', double>();
    program.add_argument("--T2_Tissue")
        .help("T2 of tissue")
        .default_value(100.)
        .scan<'g', double>();
    program.add_argument("--flow_speed")
        .help("flow speed")
        .default_value(vector<double>{0.0, 0.001, 0.002, 0.003})
        .nargs(argparse::nargs_pattern::any)
        .scan<'g', double>();
    program.add_argument("--space")
        .help("simulation space")
        .default_value(vector<double>{256., 256., 64.})
        .nargs(argparse::nargs_pattern::any)
        .scan<'g', double>();

    try
    {
        program.parse_args(argc, argv);
        assert(program.get<vector<double>>("--T1_Blood").size() == program.get<vector<int>>("--n_vessel_xy")[0] * program.get<vector<int>>("--n_vessel_xy")[1]);
        assert(program.get<vector<double>>("--T2_Blood").size() == program.get<vector<int>>("--n_vessel_xy")[0] * program.get<vector<int>>("--n_vessel_xy")[1]);
        assert(program.get<vector<double>>("--flow_speed").size() == program.get<vector<int>>("--n_vessel_xy")[0] * program.get<vector<int>>("--n_vessel_xy")[1]);
        assert(program.get<double>("--vessel_radius") > 0);
        assert(program.get<double>("--vessel_radius") < program.get<vector<double>>("--space")[0] / program.get<vector<int>>("--n_vessel_xy")[0]);
        assert(program.get<double>("--vessel_radius") < program.get<vector<double>>("--space")[1] / program.get<vector<int>>("--n_vessel_xy")[1]);
    }
    catch (const std::runtime_error &err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }
    string seq_path = program.get<string>("--seq_path");
    string save_path = program.get<string>("--save_path");
    vector<int> n_vessel_xy = program.get<vector<int>>("--n_vessel_xy");
    double vessel_radius = program.get<double>("--vessel_radius");
    int n_particle = program.get<int>("--n_particle");
    vector<double> T1 = program.get<vector<double>>("--T1_Blood");
    vector<double> T2 = program.get<vector<double>>("--T2_Blood");
    double T1_Tissue = program.get<double>("--T1_Tissue");
    double T2_Tissue = program.get<double>("--T2_Tissue");
    T1.push_back(T1_Tissue);
    T2.push_back(T2_Tissue);
    vector<double> flow_speed = program.get<vector<double>>("--flow_speed");
    vector<double> space = program.get<vector<double>>("--space");
    std::cout << program.get<string>("--save_path") << std::endl;

    if (!fs::exists(save_path))
        fs::create_directory(save_path);

    SeqLoader sq(seq_path);
    FlowPhantom phantom(
        n_vessel_xy[0],
        n_vessel_xy[1],
        vessel_radius,
        T1,
        T2,
        flow_speed,
        space,
        n_particle);
    simulate_phantom(sq.TS_list, phantom, {64, 64}, save_path);
    // std::cout << program.get<vector<int>>("--n_vessel_xy")[0] << program.get<vector<int>>("--n_vessel_xy")[1] << std::endl;
    // std::cout << program.get<double>("--vessel_radius") << std::endl;
    // std::cout << program.get<vector<double>>("--T1_Blood")[0] << std::endl;
    // std::cout << program.get<vector<double>>("--T2_Blood")[0] << std::endl;
    // std::cout << program.get<double>("--T1_Tissue") << std::endl;
    // std::cout << program.get<double>("--T2_Tissue") << std::endl;
    // std::cout << program.get<vector<double>>("--flow_speed")[0] << std::endl;
    // std::cout << program.get<vector<double>>("--space")[0] << std::endl;
    // std::cout << program.get<int>("--n_particle") << std::endl;
}