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

#include <FlowPhantom.h>
#include <M_voxel.h>
#include <Eigen/Dense>
#include <SeqSimulator.h>
#include <SeqLoader.h>
#include <filesystem>
#include <cassert>
#include "argparse.hpp"

using Eigen::Vector2d;
using std::string;
using std::vector;
namespace fs = std::filesystem;

int main(int argc, char **argv)
{
    SeqLoader sq("sequences_MOLLI/MOLLI_533_TR2.8_FA35_FOV256_K64_thick8_center_first.yaml");
    FlowPhantom phantom(
        2,
        2,
        60.,
        (vector<double>){1500., 1500., 1500., 1500., 500.},
        (vector<double>){200., 200, 200, 200, 100.},
        (vector<double>){0.0, 0.1, 0.2, 0.3},
        (vector<double>){256., 256., 64.},
        5000000);
    string save_path = "img_MOLLI/Phantom_MOLLI_533_TR2.8_FA35_FOV256_K64_thick8_center_first";
    if (!fs::exists(save_path))
        fs::create_directory(save_path);

    simulate_phantom(sq.TS_list, phantom, {64, 64}, save_path);
    return 0;
}