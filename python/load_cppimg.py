from tqdm import tqdm
import numpy as np
import matplotlib.pyplot as plt
from ruamel import yaml
import os
from MOLLI_fit import MOLLI_fit


def load_img(path, id):
    path_full = os.path.join(path, "Spatial"+str(id)+".bin")
    with open(path_full, "rb") as f:
        data = yaml.round_trip_load(f)["mat"]
    return np.asarray(data["data"]).reshape(data["rows"], data["cols"])


if __name__ == "__main__":
    MOLLI_readout_img = []
    MOLLI_readout_t = np.array(
        [200, 1200, 2200, 3200, 4200, 300, 1300, 2300]) * 1e-3
    for i in range(8):
        MOLLI_readout_img.append(load_img(
            "../Flow-Bloch-T1-mapping-cpp/img_MOLLI/533_TR2.8_FA10_FOV320_K64_center_first_64^3_323216", i))
    MOLLI_readout_img = np.asarray(
        MOLLI_readout_img)

    print(MOLLI_readout_img[:, 10, 10])

    plt.figure()
    for i in range(8):
        plt.subplot(2, 4, i+1)
        plt.imshow(MOLLI_readout_img[i])

    T1_result = np.zeros(MOLLI_readout_img[0].shape)

    for x, y in tqdm(np.ndindex(MOLLI_readout_img[0].shape)):
        T1_star, T1, A, B = MOLLI_fit(
            MOLLI_readout_t, MOLLI_readout_img[:, x, y])
        T1_result[x, y] = T1

    print(T1_result)

    plt.figure()
    plt.imshow(T1_result)
    plt.show()
