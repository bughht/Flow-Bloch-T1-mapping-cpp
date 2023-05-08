import yaml
import numpy as np
import os

gamma = 42.577478518e6  # Hz/T


class bSSFP:
    def __init__(
        self,
        TR: float,
        FA: float,
        FOV: list,  # mm
        k_shape: list,
        slice_thickness: float,  # XXX: change it into bandwidth
        pulse_duration: float,
        pulse_bandwidth: float,
        k_center_first: bool,
        sign_alter: bool,
        preparation: bool,
    ):
        self.seq = []
        (
            self.TR,
            self.FA,
            self.FOV,
            self.k_shape,
            self.slice_thickness,
            self.pulse_duration,
            self.pulse_bandwidth,
            self.k_center_first,
            self.sign_alter,
            self.preparation,
        ) = (
            TR,
            FA,
            np.array(FOV),
            np.array(k_shape),
            slice_thickness,
            pulse_duration,
            pulse_bandwidth,
            k_center_first,
            sign_alter,
            preparation,
        )
        self.data_process()

    def data_process(self):
        self.NFlip = self.k_shape[0]
        self.NADCsamples = self.k_shape[1]
        self.kFOV = self.k_shape / self.FOV
        self.kx = 1 / self.kFOV

        # [self.k_shape[0]/self.FOV[0], self.k_shape[1]/self.FOV[1]])

        # T/mm
        # self.GX = self.k_shape[0]/(2*np.pi*gamma*self.TR/4)*1e9
        # self.GY_max = self.k_shape[1]/(2*np.pi*gamma*self.TR/4)*1e9
        self.GX = (
            self.k_shape[0]
            / (2 * gamma * self.FOV[0] * (self.TR - self.pulse_duration) / 4)
            * 1e3
        )
        self.GY_max = (
            self.k_shape[1]
            / (2 * gamma * self.FOV[1] * (self.TR - self.pulse_duration) / 4)
            * 1e3
        )
        self.GZ_positive = self.pulse_bandwidth / (gamma * self.slice_thickness)
        self.GZ_negative = -(self.GZ_positive * self.pulse_duration * 2) / (
            self.TR - self.pulse_duration
        )

    def add_readout(self, t_start, FA, TR, GX, GY, kY_idx):
        FA, GX, GY, kY_idx = float(FA), float(GX), float(GY), int(kY_idx)
        GZ_negative, GZ_positive = float(self.GZ_negative), float(self.GZ_positive)
        # timestamp
        PULSE_ts = {
            "t": t_start,
            "type": "PULSE",
            "FA": FA,
            "slice_thickness": self.slice_thickness,
        }
        self.seq.append(PULSE_ts)
        GZ_ts_0 = {"t": t_start, "type": "GZ", "G": GZ_positive}
        self.seq.append(GZ_ts_0)
        GY_ts_0 = {"t": t_start + self.pulse_duration / 2, "type": "GY", "G": GY}
        GX_ts_0 = {"t": t_start + self.pulse_duration / 2, "type": "GX", "G": -GX}
        GZ_ts_1 = {
            "t": t_start + self.pulse_duration / 2,
            "type": "GZ",
            "G": GZ_negative,
        }
        self.seq.append(GZ_ts_1)
        self.seq.append(GY_ts_0)
        self.seq.append(GX_ts_0)
        GY_ts_1 = {
            "t": t_start + self.pulse_duration / 2 + (TR - self.pulse_duration) / 4,
            "type": "GY",
            "G": 0,
        }
        GX_ts_1 = {
            "t": t_start + self.pulse_duration / 2 + (TR - self.pulse_duration) / 4,
            "type": "GX",
            "G": GX,
        }
        GZ_ts_2 = {
            "t": t_start + self.pulse_duration / 2 + (TR - self.pulse_duration) / 4,
            "type": "GZ",
            "G": 0,
        }
        self.seq.append(GZ_ts_2)
        self.seq.append(GY_ts_1)
        self.seq.append(GX_ts_1)
        for adc_idx in range(self.NADCsamples):
            ADC_ts = {
                "t": float(
                    t_start
                    + self.pulse_duration / 2
                    + (TR - self.pulse_duration) / 4
                    + adc_idx
                    * (TR - self.pulse_duration)
                    / (2 * (self.NADCsamples - 1))
                ),
                "type": "ADC",
                "kx": adc_idx,
                "ky": kY_idx,
            }
            self.seq.append(ADC_ts)
        GZ_ts_3 = {
            "t": t_start + self.pulse_duration / 2 + (TR - self.pulse_duration) * 3 / 4,
            "type": "GZ",
            "G": GZ_negative,
        }
        GY_ts_2 = {
            "t": t_start + self.pulse_duration / 2 + (TR - self.pulse_duration) * 3 / 4,
            "type": "GY",
            "G": -GY,
        }
        GX_ts_2 = {
            "t": t_start + self.pulse_duration / 2 + (TR - self.pulse_duration) * 3 / 4,
            "type": "GX",
            "G": -GX,
        }
        GZ_ts_4 = {
            "t": t_start + self.pulse_duration / 2 + (TR - self.pulse_duration),
            "type": "GZ",
            "G": GZ_positive,
        }
        GY_ts_3 = {
            "t": t_start + self.pulse_duration / 2 + (TR - self.pulse_duration),
            "type": "GY",
            "G": 0,
        }
        GX_ts_3 = {
            "t": t_start + self.pulse_duration / 2 + (TR - self.pulse_duration),
            "type": "GX",
            "G": 0,
        }
        GZ_ts_5 = {
            "t": t_start + TR,
            "type": "GZ",
            "G": 0,
        }

        self.seq.append(GZ_ts_3)
        self.seq.append(GY_ts_2)
        self.seq.append(GX_ts_2)
        self.seq.append(GZ_ts_4)
        self.seq.append(GY_ts_3)
        self.seq.append(GX_ts_3)
        self.seq.append(GZ_ts_5)

    def get_twisted_index(self, N):
        center_idx = N // 2
        idx_list = [center_idx]

        twist_direction = -1
        twist_cnt = False
        twist_step = 1

        for i in range(1, N):
            next_idx = center_idx + twist_direction * twist_step
            idx_list.append(next_idx)

            twist_direction *= -1
            if twist_cnt:
                twist_step += 1
            twist_cnt = not twist_cnt

        return idx_list

    def generate(self, name):
        t_prep = 0
        if self.preparation:
            t_prep = self.TR / 2
            # self.seq.append(
            #     {
            #         "t": -(self.TR - self.pulse_duration) / 4 - self.pulse_duration / 2,
            #         "type": "GZ",
            #         "G": self.GZ_negative,
            #     }
            # )
            # self.seq.append(
            #     {"t": -self.pulse_duration / 2, "type": "GZ", "G": self.GZ_positive}
            # )
            self.seq.append(
                {
                    "t": 0,
                    "type": "PULSE",
                    "FA": self.FA / 2,
                    "slice_thickness": self.slice_thickness,
                }
            )
            # self.seq.append(
            #     {"t": self.pulse_duration / 2, "type": "GZ", "G": self.GZ_negative}
            # )
            # self.seq.append(
            #     {
            #         "t": self.pulse_duration / 2 + (self.TR - self.pulse_duration) / 4,
            #         "type": "GZ",
            #         "G": 0,
            #     }
            # )
        if not self.k_center_first:
            self.readout_kY_idx = range(self.NFlip)
        else:
            self.readout_kY_idx = self.get_twisted_index(self.NFlip)
        for readout_idx, readout_kY in enumerate(self.readout_kY_idx):
            t_start = float(t_prep + self.TR * readout_idx)
            if readout_idx == 0:
                self.seq.append(
                    {
                        "t": t_start
                        - (self.TR - self.pulse_duration) / 4
                        - self.pulse_duration / 2,
                        "type": "GZ",
                        "G": self.GZ_negative,
                    }
                )
                self.seq.append(
                    {
                        "t": t_start - self.pulse_duration / 2,
                        "type": "GZ",
                        "G": self.GZ_positive,
                    }
                )
            self.add_readout(
                t_start,
                self.FA * (((readout_idx % 2) * 2 - 1) if self.sign_alter else 1),
                self.TR,
                self.GX,
                self.GY_max * (2 * readout_kY / self.NFlip - 1),
                readout_kY,
            )
        with open(os.path.join("sequences_ssfp", name + ".yaml"), "w") as f:
            yaml.dump(self.seq, f)


if __name__ == "__main__":
    # ssfp = bSSFP(2.8, 50, [330, 330], [128, 128], 10, True, True, True)
    # ssfp.generate("TR2.8_FA50_FOV330_K128_center_first")
    # ssfp = bSSFP(2.8, 90, [500, 500], [64, 64], 10, True, True, True)
    # ssfp.generate("TR2.8_FA90_FOV500_K64_center_first")
    # ssfp = bSSFP(2.8, 90, [500, 500], [64, 64], 10, False, True, True)
    # ssfp.generate("TR2.8_FA90_FOV500_K64")
    # ssfp = bSSFP(2.8, 20, [500, 500], [64, 64], 10, True, True, True)
    # ssfp.generate("TR2.8_FA20_FOV500_K64_center_first")
    # ssfp = bSSFP(2.8, 20, [500, 500], [64, 64], 10, False, True, True)
    # ssfp.generate("TR2.8_FA0_FOV500_K64")
    # ssfp = bSSFP(2.8, 10, [320, 320], [64, 64], 10, True, True, True)
    # ssfp.generate("TR2.8_FA10_FOV320_K64_center_first")
    # ssfp = bSSFP(2.8, 10, [320, 320], [64, 64], 10, False, True, True)
    # ssfp.generate("TR2.8_FA10_FOV320_K64")
    # ssfp = bSSFP(2.8, 20, [320, 320], [64, 64], 10, True, True, True)
    # ssfp.generate("TR2.8_FA20_FOV320_K64_center_first")
    # ssfp = bSSFP(2.8, 20, [320, 320], [64, 64], 10, False, True, True)
    # ssfp.generate("TR2.8_FA20_FOV320_K64")
    # ssfp = bSSFP(2.8, 35, [256, 256], [64, 64], 8, False, True, True)
    # ssfp.generate("TR2.8_FA35_FOV256_K64_thick8")
    ssfp = bSSFP(2.8, 35, [256, 256], [64, 64], 8, 0.8, 3246, False, True, True)
    ssfp.generate("TR2.8_FA35_FOV256_K64_thick8_Gz")
