#include "SeqLoader.h"
map<string, TS_type> TS_type_map = {
    {"NONE", NONE},
    {"PULSE", PULSE},
    {"GX", GX},
    {"GY", GY},
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