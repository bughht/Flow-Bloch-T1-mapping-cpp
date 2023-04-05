import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit


def T1_fit(t, T1, A, B):
    return A - B * np.exp(-t / T1)


def T1_fit_abs(t, T1, A, B):
    return np.abs(A - B * np.exp(-t / T1))


def MAGIR(t, Mz):

    def T1_curve(t, T1, A, B):
        # return A-B*np.exp(-t/T1)
        return np.abs(A - B * np.exp(-t / T1))

    params = curve_fit(T1_curve, t, Mz, p0=[1, 100, 100], maxfev=int(1e8))
    [T1_star, A, B] = params[0]
    T1 = (B / A - 1) * T1_star
    return T1_star, T1, A, B


def MF_MAGIR(t, Mz):

    def T1_curve(t, T1, A, B):
        return A - B * np.exp(-t / T1)

    argidx = np.argsort(t)
    t = t[argidx]
    Mz = Mz[argidx]
    err = np.zeros_like(t)
    popts = []
    for i in range(len(Mz)):
        Mz_local = Mz.copy()
        Mz_local[:i] *= -1
        p_opt, p_cov = curve_fit(T1_curve,
                                 t,
                                 Mz_local,
                                 p0=[1, 100, 100],
                                 maxfev=int(1e8),
                                 check_finite=False)
        #  1, 5, 5], bounds=([0, -10, -10], [10, 10, 10]), maxfev=int(1e5))
        popts.append(p_opt)
        err_loc = abs(p_cov[0, 0])
        err[i] = err_loc

        # print(p_opt, err_loc)
        # plt.scatter(t, Mz_local)
        # plt.show()
    min_err_idx = np.argmin(err)
    T1_star, A, B = popts[min_err_idx]
    T1 = (B / A - 1) * T1_star
    return T1_star, T1, A, B


if __name__ == "__main__":
    t = np.array([200, 1200, 2200, 3200, 4200, 300, 1300, 2300]) * 1e-3
    # Mz = np.array([-0.55, 0.39, 0.63, 0.71, 0.73, -0.40, 0.42, 0.64])
    Mz0 = np.array([
        30538.6346341, 14904.48384665, 29965.31403768, 34931.51349839,
        36561.90323592, 23531.40068969, 17250.8354601, 30741.47342844
    ])
    Mz0 = np.array([
        41115.18163071, 3250.25304817, 24860.71632824, 35779.41128587,
        41318.57988047, 34764.3701684, 6336.42940291, 26416.55206831
    ])
    # Mz0 = np.array([-30538.6346341,  14904.48384665, 29965.31403768, 34931.51349839,
    #                 36561.90323592, -23531.40068969, 17250.8354601, 30741.47342844])
    # Mz0 = np.array([0.38487312, 0.15973726, 0.35128802, 0.41916806,
    # 0.44322048, 0.30324191, 0.18862595, 0.36152917])
    # Mz1 = np.array([0.19618596, 0.44258103, 0.46003101, 0.46050886,
    #                 0.46052236, 0.00838592, 0.44771084, 0.4601713])

    # Fit
    t_fit = np.arange(0, 5, 1e-5)
    T1_star, T1, A, B = MF_MAGIR(t, Mz0)
    # T1_star, T1, A, B = MAGIR(t, Mz0)
    print(T1_star, T1, A, B)
    # Mz_fit = T1_curve(t_fit, T1_star, A, B)
    # print(T1_star, A, B)
    Mz_fit = T1_fit_abs(t_fit, T1_star, A, B)
    plt.plot(t_fit, Mz_fit)

    # T1_star, T1, A, B = MOLLI_fit(t, Mz1)
    # print(T1_star, T1, A, B)
    # Mz_fit = T1_curve(t_fit, T1_star, A, B)
    # plt.plot(t_fit, Mz_fit)

    plt.scatter(t, Mz0)
    # plt.scatter(t, Mz1)
    plt.show()
