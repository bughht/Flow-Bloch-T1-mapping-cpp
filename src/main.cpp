#include <cmath>
#include <BlochSim.h>
#include <Eigen/Dense>
#include <M_voxel.h>
#include <iostream>
#include <SeqSimulator.h>
// #include <matplotlibcpp.h>

using Eigen::Matrix;
using Eigen::Matrix3d;
using Eigen::Vector3d;
using std::vector;

int main()
{
    // SeqLoader sq("sequences_ssfp/TR2.8_FA10_FOV320_K64.yaml");
    SeqLoader sq("sequences_MOLLI/MOLLI_533_TR2.8_FA10_FOV320_K64_center_first.yaml");
    // SeqLoader sq("sequences_ssfp/TR2.8_FA20_FOV500_K64_center_first.yaml");
    // M_voxel m(1000, 200, Vector3d(90, 90, 0), Vector3d(0, 0, 1));
    // simulate_single(sq.TS_list, m, {128, 128});

    // double ratio = 320.0 / 64;
    // vector<M_voxel> m_list;
    // for (int i = 0; i < 64; i++)
    // {
    //     for (int j = 0; j < 64; j++)
    //     {
    //         if (sqrt((i - 16) * (i - 16) + (j - 36) * (j - 36)) < 10)
    //         // if ((fabs(i - 32) < 16 && fabs(j - 32) < 16))
    //         {
    //             // for (int sample_idx = -0; sample_idx < 1; sample_idx++)

    //             m_list.push_back(M_voxel(1000, 50, Vector3d((i - 32) * ratio, (j - 32) * ratio, 0), Vector3d(0, 0, 1.0)));
    //             // m_list.push_back(
    //             //     M_voxel(1000, 200, Vector3d((i - 32 + rand() / RAND_MAX * 2 - 1) * ratio, (j - 32 + rand() / RAND_MAX * 2 - 1) * 2 * ratio, 0), Vector3d(0, 0, 0.9)));
    //         }
    //         else
    //         {
    //             m_list.push_back(M_voxel(1000, 50, Vector3d((i - 32) * ratio, (j - 32) * ratio, 0), Vector3d(0, 0, 0.6)));
    //             // m_list.push_back(
    //             //     M_voxel(500, 100, Vector3d((i - 32) * ratio, (j - 32) * ratio * 2, 0), Vector3d(0, 0, 0.6)));
    //             // m_list.push_back(
    //             //     M_voxel(1000, 200, Vector3d(i * 5, j * 5, 0), Vector3d(0, 0, 1)));
    //         }
    //     }
    // }
    // simulate_plane(sq.TS_list, m_list, {64, 64});
    double ratio = 320.0 / 64;
    vector<M_voxel> m_list;
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            for (int k = 0; k < 64; k++)
            {
                if (sqrt((i - 32) * (i - 32) + (j - 32) * (j - 32) + (k - 16) * (k - 16)) < 10)
                {
                    m_list.push_back(M_voxel(1500, 200, Vector3d((i - 32) * ratio, (j - 32) * ratio, (k - 32) * ratio), Vector3d(0, 0, 1.0), Vector3d(0, 0, 0)));
                }
                else
                {
                    m_list.push_back(M_voxel(600, 100, Vector3d((i - 32) * ratio, (j - 32) * ratio, (k - 32) * ratio), Vector3d(0, 0, 1.0), Vector3d(0, 0, 0)));
                }
            }
        }
    }
    // simulate_volume(sq.TS_list, m_list, {64, 64}, "img_MOLLI/533_TR2.8_FA20_FOV320_K64_center_first");
    simulate_volume(sq.TS_list, m_list, {64, 64}, "img_MOLLI/533_TR2.8_FA10_FOV320_K64_center_first_64^3_323216");
}