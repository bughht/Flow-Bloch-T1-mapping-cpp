#include <BlochSim.h>
#include <Eigen/Dense>
#include <M_voxel.h>
#include <iostream>
#include <SeqSimulator.h>
#include <matplotlibcpp.h>

using Eigen::Matrix3d;
using Eigen::Vector3d;

int main()
{
  Vector3d m;
  m << 0, 0, -1;
  for (int i = 0; i < 100; i++)
  {
    FP_args args = freeprecess(10, 1000, 100, 0);
    m = args.A * m + args.B;
    std::cout << "m =" << std::endl
              << m << std::endl;
  }
}