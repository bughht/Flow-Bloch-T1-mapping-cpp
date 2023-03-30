#include "SeqSimulator.h"
#include "tqdm.hpp"

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

    // plt::subplot(3, 1, 1);
    // plt::plot(t_readout, Mz_h);
    // plt::subplot(3, 1, 2);
    // plt::plot(t_readout, Mxy_h);
    // plt::subplot(3, 1, 3);
    // plt::plot(t_readout, Phase_h);
    // plt::show();

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

    vector<double> spx, spy;
    vector<double> Mx, My;
    for (int i = 0; i < m_plane.size(); i++)
    {
        spx.push_back(m_plane[i].pos[0]);
        spy.push_back(m_plane[i].pos[1]);
        Mx.push_back(m_plane[i].M[0]);
        My.push_back(m_plane[i].M[1]);
    }

    int adc_id = 0;
    bool adc_now = false;

    for (TS ts : tq::tqdm(seq))
    // for (int ts_idx : tq::trange(seq.size()))
    {
        // TS &ts = seq[ts_idx];
        // for (M_voxel m : m_plane)
        for (int m_idx = 0; m_idx < m_plane.size(); m_idx++)
        {
            M_voxel &m = m_plane[m_idx];
            // std::cout << ts.t << ", " << t << ", " << ts.t - t << ", " << Gx << ", " << Gy << std::endl;
            m.free_precess(ts.t - t, Gx, Gy);
            Mx[m_idx] = m.readout().Mxy.real();
            My[m_idx] = m.readout().Mxy.imag();
            if (ts.type == PULSE)
            {
                m.flip(ts.FA);
            }
            if (ts.type == ADC)
            {
                if (!adc_now)
                {
                    adc_id++;
                    adc_now = true;
                }
                adc = m.readout();
                if (m_idx == 0)
                {
                    t_readout.push_back(ts.t);
                    signal_readout.push_back(adc);
                }
                if (adc_id % 2)
                {
                    k_space_real.at<double>(ts.kx, ts.ky) += adc.Mxy.real();
                    k_space_imag.at<double>(ts.kx, ts.ky) += adc.Mxy.imag();
                }
                else
                {
                    k_space_real.at<double>(ts.kx, ts.ky) -= adc.Mxy.real();
                    k_space_imag.at<double>(ts.kx, ts.ky) -= adc.Mxy.imag();
                }
                // std::cout << "m_idx: " << m_idx << " Pos " << m.pos << " Mxy " << adc.Mxy.real() << " " << adc.Mxy.imag() << std::endl;
            }
            else
            {
                if (adc_now)
                    adc_now = false;
            }
        }
        switch (ts.type)
        {
        case GX:
            Gx = ts.G;
            // std::cout << std::endl
            //   << ts.type << "\t" << ts.t << "\t" << Gx << "\t" << Gy << std::endl;
            break;
        case GY:
            Gy = ts.G;
            // std::cout << std::endl
            //   << ts.type << "\t" << ts.t << "\t" << Gx << "\t" << Gy << std::endl;
            break;
        default:
            break;
        }
        // plt::figure();
        // plt::quiver(spx, spy, Mx, My);
        // plt::show();

        // std::cout << std::endl
        //           << "ADC " << adc_id << std::endl;
        t = ts.t;

        // std::cout << "t " << t << " t_loc " << ts.t << " M " << m_idx << std::endl;
        //   << m.M << std::endl;
        // 1
    }
    vector<double> Mxy_h, Phase_h, Mz_h;
    for (ADC_args adc : signal_readout)
    {
        Mxy_h.push_back(adc.amplitude);
        Phase_h.push_back(adc.phase);
        Mz_h.push_back(adc.Mz);
    }

    // plt::subplot(3, 1, 1);
    // plt::plot(t_readout, Mz_h);
    // plt::subplot(3, 1, 2);
    // plt::plot(t_readout, Mxy_h);
    // plt::subplot(3, 1, 3);
    // plt::plot(t_readout, Phase_h);
    // plt::show();

    cv::Mat k_space_[2] = {k_space_real, k_space_imag};
    cv::Mat spatial_[2] = {spatial_real, spatial_imag};

    cv::Mat k_space, spatial;
    cv::merge(k_space_, 2, k_space);

    // cv::flip(k_space(roi_upleft), k_space(roi_upleft), -1);
    // cv::flip(k_space(roi_upright), k_space(roi_upright), -1);
    // cv::flip(k_space(roi_downleft), k_space(roi_downleft), -1);
    // cv::flip(k_space(roi_downright), k_space(roi_downright), -1);

    cv::idft(k_space, spatial);
    cv::split(spatial, spatial_);
    cv::magnitude(spatial_[0], spatial_[1], spatial);
    cv::magnitude(k_space_[0], k_space_[1], k_space);
    // spatial /= (spatial.rows * spatial.cols);
    // spatial /= tan(10 * 180 / M_PI);
    cv::normalize(spatial, spatial, 0, 1, cv::NORM_MINMAX);
    // cv::normalize(k_space, k_space, 0, 1, cv::NORM_MINMAX);

    auto roi_upleft = cv::Rect(0, 0, k_shape[1] / 2, k_shape[0] / 2);
    auto roi_upright = cv::Rect(k_shape[1] / 2, 0, k_shape[1] / 2, k_shape[0] / 2);
    auto roi_downleft = cv::Rect(0, k_shape[0] / 2, k_shape[1] / 2, k_shape[0] / 2);
    auto roi_downright = cv::Rect(k_shape[1] / 2, k_shape[0] / 2, k_shape[1] / 2, k_shape[0] / 2);
    // auto roi_up = cv::Rect(0, 0, k_shape[1], k_shape[0] / 2);
    // auto roi_down = cv::Rect(0, k_shape[0] / 2, k_shape[1], k_shape[0] / 2);
    // cv::flip(spatial(roi_up), spatial(roi_up), 0);
    // cv::flip(spatial(roi_down), spatial(roi_down), 0);
    cv::flip(spatial(roi_upleft), spatial(roi_upleft), -1);
    cv::flip(spatial(roi_upright), spatial(roi_upright), -1);
    cv::flip(spatial(roi_downleft), spatial(roi_downleft), -1);
    cv::flip(spatial(roi_downright), spatial(roi_downright), -1);

    cv::namedWindow("k_space", cv::WINDOW_NORMAL);
    cv::namedWindow("spatial", cv::WINDOW_NORMAL);
    cv::imshow("k_space", k_space / 20);
    cv::imshow("spatial", spatial);
    cv::waitKey(0);
}

void simulate_volume(vector<TS> seq, vector<M_voxel> m_voxels, vector<int> kshape, fs::path save_path)
{
    double t = 0;
    double Gx = 0, Gy = 0;
    vector<double> t_readout;

    cv::Mat k_space_real = cv::Mat_<double>(kshape[0], kshape[1], 0.0);
    cv::Mat k_space_imag = cv::Mat_<double>(kshape[0], kshape[1], 0.0);
    cv::Mat spatial_real = cv::Mat_<double>(kshape[0], kshape[1], 0.0);
    cv::Mat spatial_imag = cv::Mat_<double>(kshape[0], kshape[1], 0.0);

    ADC_args adc(0, 0, 0);

    int ADC_counter = 0;
    bool ADC_now = false;
    int readout_id = 0;
    for (TS ts : tq::tqdm(seq))
    {
        if (ts.type == READOUT_START)
        {
            std::cout << "START READOUT" << std::endl;
            k_space_real = cv::Mat_<double>(kshape[0], kshape[1], 0.0);
            k_space_imag = cv::Mat_<double>(kshape[0], kshape[1], 0.0);
        }
        if (ts.type == READOUT_END)
        {
            std::cout << "END READOUT" << std::endl;
            cv::Mat k_space_[2] = {k_space_real, k_space_imag};
            cv::Mat spatial_[2] = {spatial_real, spatial_imag};
            cv::Mat k_space, spatial;
            cv::merge(k_space_, 2, k_space);
            cv::idft(k_space, spatial);
            cv::split(spatial, spatial_);
            cv::magnitude(spatial_[0], spatial_[1], spatial);
            cv::magnitude(k_space_[0], k_space_[1], k_space);
            // cv::normalize(spatial, spatial, 0, 1, cv::NORM_MINMAX);
            auto roi_upleft = cv::Rect(0, 0, kshape[1] / 2, kshape[0] / 2);
            auto roi_upright = cv::Rect(kshape[1] / 2, 0, kshape[1] / 2, kshape[0] / 2);
            auto roi_downleft = cv::Rect(0, kshape[0] / 2, kshape[1] / 2, kshape[0] / 2);
            auto roi_downright = cv::Rect(kshape[1] / 2, kshape[0] / 2, kshape[1] / 2, kshape[0] / 2);
            cv::flip(spatial(roi_upleft), spatial(roi_upleft), -1);
            cv::flip(spatial(roi_upright), spatial(roi_upright), -1);
            cv::flip(spatial(roi_downleft), spatial(roi_downleft), -1);
            cv::flip(spatial(roi_downright), spatial(roi_downright), -1);
            // cv::namedWindow("k_space", cv::WINDOW_NORMAL);
            // cv::namedWindow("spatial", cv::WINDOW_NORMAL);
            // cv::imshow("k_space", k_space / 20);
            // cv::imshow("spatial", spatial);
            // cv::waitKey(0);

            fs::path kspace_path = save_path / ("Kspace" + std::to_string(readout_id) + ".bin");
            fs::path spatial_path = save_path / ("Spatial" + std::to_string(readout_id) + ".bin");

            cv::FileStorage fs_kspace(kspace_path.string(), cv::FileStorage::WRITE);
            cv::FileStorage fs_spatial(spatial_path.string(), cv::FileStorage::WRITE);
            fs_kspace << "mat" << k_space;
            fs_spatial << "mat" << spatial;

            readout_id++;
        }
#pragma omp parallel for num_threads(64) shared(m_voxels, kspace_real, kspace_imag, ADC_now)
        for (int m_idx = 0; m_idx < m_voxels.size(); m_idx++)
        {
            M_voxel &m = m_voxels[m_idx];
            m.free_precess(ts.t - t, Gx, Gy);
            if (ts.type == PULSE)
            {
                if (std::abs(ts.slice_thickness) > 1e-9)
                {
                    if (std::abs(m.get_pos()[2]) < ts.slice_thickness / 2)
                        m.flip(ts.FA);
                }
                else
                {
                    m.flip(ts.FA);
                }
            }
            if (ts.type == ADC)
            {
                if (!ADC_now)
                {
                    ADC_now = true;
                    ADC_counter++;
                }
                adc = m.readout();
                if (ADC_counter % 2)
                {
#pragma omp atomic update
                    k_space_real.at<double>(ts.kx, ts.ky) += -adc.Mxy.real() / m_voxels.size();
#pragma omp atomic update
                    k_space_imag.at<double>(ts.kx, ts.ky) += -adc.Mxy.imag() / m_voxels.size();
                }
                else
                {
#pragma omp atomic update
                    k_space_real.at<double>(ts.kx, ts.ky) += -adc.Mxy.real() / m_voxels.size();
#pragma omp atomic update
                    k_space_imag.at<double>(ts.kx, ts.ky) += -adc.Mxy.imag() / m_voxels.size();
                }
            }
            else
                ADC_now = false;
        }
        switch (ts.type)
        {
        case GX:
            Gx = ts.G;
            break;
        case GY:
            Gy = ts.G;
            break;
        default:
            break;
        }
        t = ts.t;
    }
}
