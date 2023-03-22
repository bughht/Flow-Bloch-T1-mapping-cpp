#include<BlochSim.h>
#include<iostream>
#include<Eigen/Dense>

using Eigen::Matrix3d;
using Eigen::Vector3d;
 
int main()
{
  Vector3d m;
  m<<0,0,0;
  for(int i=0;i<100;i++){
    FP_args args = freeprecess(10,1000,100,0);
    m = args.A*m + args.B;
    std::cout << "m =" << std::endl << m << std::endl;
  }
}