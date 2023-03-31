import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit


def T1_curve(t, T1, A, B):
    return np.abs(A-B*np.exp(-t*T1))
    # return A-B*np.exp(-t*T1)


def MOLLI_fit(t, Mz):
    params = curve_fit(T1_curve, t, Mz, p0=[1, 0.5, 1.5], maxfev=int(1e5))
    [T1_star, A, B] = params[0]
    T1 = (B/A-1)*T1_star
    return T1_star, T1, A, B


if __name__ == "__main__":
    t = np.array([200, 1200, 2200, 3200, 4200, 300, 1300, 2300]) * 1e-3
    # Mz = np.array([-0.55, 0.39, 0.63, 0.71, 0.73, -0.40, 0.42, 0.64])
    Mz0 = np.array([0.38487312, 0.15973726, 0.35128802, 0.41916806,
                    0.44322048, 0.30324191, 0.18862595, 0.36152917])
    Mz1 = np.array([0.19618596, 0.44258103, 0.46003101, 0.46050886,
                    0.46052236, 0.00838592, 0.44771084, 0.4601713])

    # Fit
    t_fit = np.arange(0, 5, 1e-5)
    T1_star, T1, A, B = MOLLI_fit(t, Mz0)
    print(T1_star, T1, A, B)
    Mz_fit = T1_curve(t_fit, T1_star, A, B)
    plt.plot(t_fit, Mz_fit)

    T1_star, T1, A, B = MOLLI_fit(t, Mz1)
    print(T1_star, T1, A, B)
    Mz_fit = T1_curve(t_fit, T1_star, A, B)
    plt.plot(t_fit, Mz_fit)

    plt.scatter(t, Mz0)
    plt.scatter(t, Mz1)
    plt.show()
