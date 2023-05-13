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

#include "SeqLoader.h"
map<string, TS_type> TS_type_map = {
    {"NONE", NONE},
    {"PULSE", PULSE},
    {"GX", GX},
    {"GY", GY},
    {"GZ", GZ},
    {"ADC", ADC},
    {"READOUT_START", READOUT_START},
    {"READOUT_END", READOUT_END}};

TS::TS()
{
    this->FA = 0;
    this->G = 0;
    this->t = 0;
    this->slice_thickness = -1;
    this->type = NONE;
}

SeqLoader::SeqLoader(string seq_file)
{
    this->seq_file = seq_file;
    this->load_seq();
    this->parse_seq();
}

SeqLoader::~SeqLoader()
{
}

void SeqLoader::load_seq()
{
    try
    {
        this->seq_node = YAML::LoadFile(this->seq_file);
    }
    catch (...)
    {
        std::cout << "Load File Error" << std::endl;
        return;
    }
}

void SeqLoader::print_seq()
{
    for (auto ts : this->TS_list)
    {
        std::cout << "type: " << ts.type << std::endl;
        std::cout << "t: " << ts.t << std::endl;
    }
}

void SeqLoader::parse_seq()
{
    for (auto ts : this->seq_node)
    {
        TS_type type = TS_type_map[ts["type"].as<string>()];
        TS ts_obj;
        ts_obj.type = type;
        ts_obj.t = ts["t"].as<double>();
        switch (type)
        {
        case PULSE:
            ts_obj.FA = ts["FA"].as<double>();
            if (ts["slice_thickness"].IsDefined())
                ts_obj.slice_thickness = ts["slice_thickness"].as<double>();
            else
                ts_obj.slice_thickness = 0.0;
            break;
        case GX:
            ts_obj.G = ts["G"].as<double>();
            break;
        case GY:
            ts_obj.G = ts["G"].as<double>();
            break;
        case GZ:
            ts_obj.G = ts["G"].as<double>();
            break;
        case ADC:
            if (ts["kx"].IsDefined())
                ts_obj.kx = ts["kx"].as<double>();
            if (ts["ky"].IsDefined())
                ts_obj.ky = ts["ky"].as<double>();
            break;
        }
        this->TS_list.push_back(ts_obj);
    }
}