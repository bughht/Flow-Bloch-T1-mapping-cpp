#include <SeqLoader.h>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    SeqLoader sb("sequences_ssfp/TR2.8_FA10.yaml");
    auto ts_list = sb.TS_list;
    for (auto ts : ts_list)
    {
        std::cout << "type: " << ts.type << std::endl;
        std::cout << "t: " << ts.t << std::endl;
    }
    return 0;
}