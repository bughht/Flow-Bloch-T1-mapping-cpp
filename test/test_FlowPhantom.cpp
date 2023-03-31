#include <FlowPhantom.h>
#include <M_voxel.h>
#include <Eigen/Dense>

using Eigen::Vector2d;
using std::vector;

int main(void)
{
    FlowPhantom phantom(
        2,
        2,
        10.,
        (vector<double>){1000., 2000., 3000., 4000., 500.},
        (vector<double>){40., 50., 60., 70., 80.},
        (vector<double>){70., 80., 90., 100.},
        (vector<double>){64., 64., 64.},
        10000);
    for (M_voxel &m : phantom.particles)
    {
        // std::cout << center << std::endl;
        if (m.flow_speed[2] > 0)
            std::cout << m.pos[0] << " " << m.pos[1] << " " << m.pos[2] << " " << m.flow_speed[2] << std::endl;
    }
    phantom.free_precess(0.1, 0, 0);
    return 0;
}