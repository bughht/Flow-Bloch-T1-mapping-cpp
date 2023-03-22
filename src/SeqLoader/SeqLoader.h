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
    ADC
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