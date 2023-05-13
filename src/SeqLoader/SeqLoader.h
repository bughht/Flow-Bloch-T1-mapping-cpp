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

#ifndef SEQLOADER_H
#define SEQLOADER_H

#include <string>
#include <iostream>
#include <yaml-cpp/yaml.h>

using std::map;
using std::string;
using std::vector;
using YAML::Node;

enum TS_type
{
    NONE,
    PULSE,
    GX,
    GY,
    GZ,
    ADC,
    READOUT_START,
    READOUT_END
};

struct TS
{
    TS_type type;
    double FA;
    double G;
    double t;
    double kx, ky;
    double slice_thickness;
    TS();
};

class SeqLoader
{
private:
    string seq_file;
    Node seq_node;
    void load_seq();
    void parse_seq();

public:
    vector<TS> TS_list;
    SeqLoader(std::string seq_file);
    void print_seq();
    ~SeqLoader();
};

#endif