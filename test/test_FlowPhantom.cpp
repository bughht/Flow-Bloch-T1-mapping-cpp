#include <FlowPhantom.h>
#include <M_voxel.h>
#include <Eigen/Dense>
#include <SeqSimulator.h>
#include <SeqLoader.h>
#include <filesystem>

using Eigen::Vector2d;
using std::string;
using std::vector;
namespace fs = std::filesystem;

int main(void)
{
    SeqLoader sq("sequences_MOLLI/MOLLI_533_TR2.8_FA35_FOV256_K64_thick8_center_first.yaml");
    FlowPhantom phantom(
        2,
        2,
        50.,
        // (vector<double>){1500., 1300., 1100., 900., 500.},
        (vector<double>){1500., 1500., 1500., 1500., 500.},
        (vector<double>){200., 200, 200, 200, 50.},
        (vector<double>){0.000, 0.001, 0.000, 0.000},
        (vector<double>){256., 256., 8.},
        500000);
    string save_path = "img_MOLLI/Phantom_MOLLI_533_TR2.8_FA35_FOV256_K64_thick8_center_first";
    if (!fs::exists(save_path))
        fs::create_directory(save_path);

    simulate_phantom(sq.TS_list, phantom, {64, 64}, save_path);
    return 0;
}