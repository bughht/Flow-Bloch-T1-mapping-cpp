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