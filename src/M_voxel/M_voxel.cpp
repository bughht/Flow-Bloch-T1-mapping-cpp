#include "M_voxel.h"

ADC_args::ADC_args(Vector3d M)
{
    this->M = M;
    this->Mz = M(2);
    this->Mxy = {M(0), M(1)};
    this->amplitude = abs(Mxy);
    this->phase = arg(Mxy);
}

ADC_args::ADC_args(double Mx, double My, double Mz)
{
    this->M << Mx, My, Mz;
    this->Mz = Mz;
    this->Mxy = {Mx, My};
    this->amplitude = abs(Mxy);
    this->phase = arg(Mxy);
}

M_voxel::M_voxel(double T1, double T2, Vector3d pos = Vector3d(0, 0, 0), Vector3d M = Vector3d(0, 0, 1))
{
    this->T1 = T1;
    this->T2 = T2;
    this->pos = pos;
    this->M = M;
}

M_voxel::~M_voxel()
{
}

void M_voxel::flip(double FA)
{
    double theta = FA * M_PI / 180;
    Matrix3d R = Ry(theta);
    // std::cout << "origin" << this->M.transpose() << std::endl;
    this->M = R * this->M;
    // std::cout << "flipped" << this->M.transpose() << std::endl;
}

void M_voxel::free_precess(double T, double Gx, double Gy)
{
    // std::cout << "Gx: " << Gx << ", Gy: " << Gy << ", t: " << T << std::endl;
    double df = GAMMA * Gx * this->pos(0) + GAMMA * Gy * this->pos(1);
    FP_args AB = freeprecess(T, this->T1, this->T2, df);
    this->M = AB.A * this->M + AB.B;
}

ADC_args M_voxel::readout()
{
    ADC_args adc(this->M);
    return adc;
}