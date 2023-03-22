#include "M_voxel.h"

ADC_args::ADC_args(void)
{
    this->M = Vector3d(0, 0, 0);
    this->Mz = 0;
    this->Mxy = {0, 0};
    this->amplitude = 0;
    this->phase = 0;
}

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
    Matrix3d R = Rz(FA);
    this->M = R * this->M;
}

void M_voxel::free_precess(double T, double Gx, double Gy)
{
    double df = Gx * this->pos(0) + Gy * this->pos(1);
    FP_args AB = freeprecess(T, this->T1, this->T2, df);
    this->M = AB.A * this->M + AB.B;
}

ADC_args M_voxel::readout()
{
    ADC_args adc(this->M);
    return adc;
}