#include <cmath>
#include <BlochSim.h>
#include <Eigen/Dense>
#include <M_voxel.h>
#include <iostream>
#include <SeqSimulator.h>
#include <matplotlibcpp.h>

using Eigen::Matrix;
using Eigen::Matrix3d;
using Eigen::Vector3d;
using std::vector;

int main()
{
    SeqLoader sq("sequences_ssfp/TR2.8_FA30.yaml");
    // M_voxel m(1000, 200, Vector3d(5, 3, 0), Vector3d(0, 0, 1));
    // simulate_single(sq.TS_list, m, {128, 128});

    vector<M_voxel> m_list;
    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 128; j++)
        {
            if (sqrt((i - 20) * (i - 20) + (j - 10) * (j - 10)) < 20)
            {

                m_list.push_back(
                    M_voxel(5000, 200, Vector3d(i * 5, j * 5, 0), Vector3d(0, 0, -.5)));
            }
            else
            {
                m_list.push_back(
                    M_voxel(1000, 200, Vector3d(i * 5, j * 5, 0), Vector3d(0, 0, 1)));
            }
        }
    }
    simulate_plane(sq.TS_list, m_list, {128, 128});
}