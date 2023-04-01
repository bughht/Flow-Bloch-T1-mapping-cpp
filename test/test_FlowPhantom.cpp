#include <FlowPhantom.h>
#include <M_voxel.h>
#include <Eigen/Dense>
#include <SeqSimulator.h>
#include <SeqLoader.h>

using Eigen::Vector2d;
using std::vector;

int main(void)
{
    SeqLoader sq("sequences_MOLLI/MOLLI_533_TR2.8_FA10_FOV320_K64_center_first.yaml");
    FlowPhantom phantom(
        2,
        2,
        60.,
        (vector<double>){1500., 1300., 1100., 900., 500.},
        (vector<double>){200., 180, 160, 140, 100.},
        (vector<double>){0.0, 0.0, 0.0, 0.0, 0.0},
        (vector<double>){320., 320., 10.},
        1000000);
    simulate_phantom(sq.TS_list, phantom, {64, 64}, "img_MOLLI/Phantom_MOLLI_533_TR2.8_FA10_FOV320_K64_center_first");

    // for (M_voxel &m : phantom.particles)
    // {
    //     // std::cout << center << std::endl;
    //     if (m.flow_speed[2] > 0)
    //         std::cout << m.pos[0] << " " << m.pos[1] << " " << m.pos[2] << " " << m.flow_speed[2] << std::endl;
    // }
    // phantom.free_precess(10000, 10, 10);
    // phantom.flip(90, 10);
    // // phantom.free_precess(5, 10, 10);
    // std::cout << phantom.adc() << std::endl;
    return 0;
}