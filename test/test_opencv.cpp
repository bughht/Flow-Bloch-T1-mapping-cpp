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