#include "SeqSimulator.h"

void simulate_single(vector<TS> seq, M_voxel m, vector<int> k_shape)
{
    double t = 0;
    double Gx = 0.0, Gy = 0.0;
    vector<double> t_readout;
    vector<ADC_args> signal_readout;
    cv::Mat k_space_real = cv::Mat_<double>(k_shape[0], k_shape[1]), k_space_imag = cv::Mat_<double>(k_shape[0], k_shape[1]);
    cv::Mat spatial_real = cv::Mat_<double>(k_shape[0], k_shape[1]), spatial_imag = cv::Mat_<double>(k_shape[0], k_shape[1]);

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
            t_readout.push_back(ts.t);
            signal_readout.push_back(adc);
            k_space_real.at<double>(ts.kx, ts.ky) = adc.Mxy.real();
            k_space_imag.at<double>(ts.kx, ts.ky) = adc.Mxy.imag();
            break;
        default:
            break;
        }
        t = ts.t;
    }
    vector<double> Mxy_h, Phase_h, Mz_h;
    for (ADC_args adc : signal_readout)
    {
        Mxy_h.push_back(adc.amplitude);
        Phase_h.push_back(adc.phase);
        Mz_h.push_back(adc.Mz);
    }

    plt::subplot(3, 1, 1);
    plt::plot(t_readout, Mz_h);
    plt::subplot(3, 1, 2);
    plt::plot(t_readout, Mxy_h);
    plt::subplot(3, 1, 3);
    plt::plot(t_readout, Phase_h);
    plt::show();

    cv::Mat k_space_[2] = {k_space_real, k_space_imag};
    cv::Mat spatial_[2] = {spatial_real, spatial_imag};

    cv::Mat k_space, spatial;
    cv::merge(k_space_, 2, k_space);
    cv::idft(k_space, spatial);
    cv::split(spatial, spatial_);
    cv::magnitude(spatial_[0], spatial_[1], spatial);
    cv::magnitude(k_space_[0], k_space_[1], k_space);
    cv::normalize(spatial, spatial, 0, 1, cv::NORM_MINMAX);

    cv::namedWindow("k_space", cv::WINDOW_NORMAL);
    cv::namedWindow("spatial", cv::WINDOW_NORMAL);
    cv::imshow("k_space", k_space);
    cv::imshow("spatial", spatial);
    cv::waitKey(0);
}

void simulate_plane(vector<TS> seq, vector<M_voxel> m_plane, vector<int> k_shape)
{
    double t = 0;
    double Gx = 0.0, Gy = 0.0;
    vector<double> t_readout;
    vector<ADC_args> signal_readout;
    cv::Mat k_space_real = cv::Mat_<double>(k_shape[0], k_shape[1], 0.0), k_space_imag = cv::Mat_<double>(k_shape[0], k_shape[1], 0.0);
    cv::Mat spatial_real = cv::Mat_<double>(k_shape[0], k_shape[1], 0.0), spatial_imag = cv::Mat_<double>(k_shape[0], k_shape[1], 0.0);

    ADC_args adc(0, 0, 0);

    for (TS ts : seq)
    {
        // for (M_voxel m : m_plane)
        for (int m_idx = 0; m_idx < m_plane.size(); m_idx++)
        {
            M_voxel &m = m_plane[m_idx];
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
                if (m_idx == 0)
                {
                    t_readout.push_back(ts.t);
                    signal_readout.push_back(adc);
                }
                k_space_real.at<double>(ts.kx, ts.ky) += adc.Mxy.real();
                k_space_imag.at<double>(ts.kx, ts.ky) += adc.Mxy.imag();
                break;
            default:
                break;
            }
        }
        // std::cout << "t " << t << " t_loc " << ts.t << " M " << m_idx << std::endl;
        //   << m.M << std::endl;
        // 1
        t = ts.t;
    }
    vector<double> Mxy_h, Phase_h, Mz_h;
    for (ADC_args adc : signal_readout)
    {
        Mxy_h.push_back(adc.amplitude);
        Phase_h.push_back(adc.phase);
        Mz_h.push_back(adc.Mz);
    }

    plt::subplot(3, 1, 1);
    plt::plot(t_readout, Mz_h);
    plt::subplot(3, 1, 2);
    plt::plot(t_readout, Mxy_h);
    plt::subplot(3, 1, 3);
    plt::plot(t_readout, Phase_h);
    plt::show();

    cv::Mat k_space_[2] = {k_space_real, k_space_imag};
    cv::Mat spatial_[2] = {spatial_real, spatial_imag};

    cv::Mat k_space, spatial;
    cv::merge(k_space_, 2, k_space);
    cv::idft(k_space, spatial);
    cv::split(spatial, spatial_);
    cv::magnitude(spatial_[0], spatial_[1], spatial);
    cv::magnitude(k_space_[0], k_space_[1], k_space);
    cv::normalize(spatial, spatial, 0, 1, cv::NORM_MINMAX);

    cv::namedWindow("k_space", cv::WINDOW_NORMAL);
    cv::namedWindow("spatial", cv::WINDOW_NORMAL);
    cv::imshow("k_space", k_space);
    cv::imshow("spatial", spatial);
    cv::waitKey(0);
}