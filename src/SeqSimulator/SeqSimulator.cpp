#include "SeqSimulator.h"

void simulate_single(vector<TS> seq, M_voxel m, vector<int> k_shape)
{
    double t = 0;
    double Gx = 0.0, Gy = 0.0;
    vector<double> t_readout;
    vector<ADC_args> signal_readout;
    MatrixXcd k_space = MatrixXcd::Zero(k_shape[0], k_shape[1]);
    MatrixXcd spatial = MatrixXcd::Zero(k_shape[0], k_shape[1]);
    ADC_args adc(0, 0, 0);

    for (TS ts : seq)
    {
        m.free_precess(ts.t - t, Gx, Gy);
        switch (ts.type)
        {
        case PULSE:
            m.flip(ts.FA);
            break;
        case GX:
            Gx = ts.G;
            break;
        case GY:
            Gy = ts.G;
            break;
        case ADC:
            adc = m.readout();
            signal_readout.push_back(adc);
            k_space(ts.kx, ts.ky) = adc.Mxy;
            break;
        default:
            break;
        }
        t = ts.t;
    }
}