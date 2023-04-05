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

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using std::string;
using namespace cv;

int main()
{
    string imageName("/home/bughht/Downloads/nxbj.jpeg"); // by default
    Mat image;
    image = imread(imageName, IMREAD_COLOR);
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    waitKey(0);
    return 0;
}