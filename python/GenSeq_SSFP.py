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
        slice_thickness: float,  # TODO: change it into bandwidth
        k_center_first: bool,
        sign_alter: bool,
        preparation: bool
    ):
        self.seq = []
        self.TR, self.FA, self.FOV, self.k_shape, self.slice_thickness, self.k_center_first, self.sign_alter, self.preparation = TR, FA, np.array(
            FOV), np.array(k_shape), slice_thickness, k_center_first, sign_alter, preparation
        self.data_process()

    def data_process(self):
        self.NFlip = self.k_shape[0]
        self.NADCsamples = self.k_shape[1]
        self.kFOV = self.k_shape/self.FOV
        self.kx = 1/self.kFOV

        # [self.k_shape[0]/self.FOV[0], self.k_shape[1]/self.FOV[1]])

        # T/mm
        # self.GX = self.k_shape[0]/(2*np.pi*gamma*self.TR/4)*1e9
        # self.GY_max = self.k_shape[1]/(2*np.pi*gamma*self.TR/4)*1e9
        self.GX = self.k_shape[0]/(2*gamma*self.FOV[0]*self.TR/4)*1e3
        self.GY_max = self.k_shape[1]/(2*gamma*self.FOV[1]*self.TR/4)*1e3

    def add_readout(self, t_start, FA, TR, GX, GY, kY_idx):
        FA,  GX, GY, kY_idx = float(FA),  float(GX), float(GY), int(kY_idx)
        # timestamp
        PULSE_ts = {
            "t": t_start,
            "type": "PULSE",
            "FA": FA,
            "slice_thickness": self.slice_thickness
        }
        GY_ts_0 = {
            "t": t_start,
            "type": "GY",
            "G": GY
        }
        GX_ts_0 = {
            "t": t_start,
            "type": "GX",
            "G": -GX
        }
        GY_ts_1 = {
            "t": t_start+TR/4,
            "type": "GY",
            "G": 0
        }
        GX_ts_1 = {
            "t": t_start+TR/4,
            "type": "GX",
            "G": GX
        }
        self.seq.append(PULSE_ts)
        self.seq.append(GY_ts_0)
        self.seq.append(GX_ts_0)
        self.seq.append(GY_ts_1)
        self.seq.append(GX_ts_1)
        for adc_idx in range(self.NADCsamples):
            ADC_ts = {
                "t": float(t_start+TR/4+adc_idx*TR/(2*(self.NADCsamples-1))),
                "type": "ADC",
                "kx": adc_idx,
                "ky": kY_idx
            }
            self.seq.append(ADC_ts)
        GY_tx_2 = {
            "t": t_start+TR/4+TR/2,
            "type": "GY",
            "G": -GY
        }
        GX_tx_2 = {
            "t": t_start+TR/4+TR/2,
            "type": "GX",
            "G": -GX
        }
        GY_tx_3 = {
            "t": t_start+TR,
            "type": "GY",
            "G": 0
        }
        GX_tx_3 = {
            "t": t_start+TR,
            "type": "GX",
            "G": 0
        }
        self.seq.append(GY_tx_2)
        self.seq.append(GX_tx_2)
        self.seq.append(GY_tx_3)
        self.seq.append(GX_tx_3)

    def get_twisted_index(self, N):
        center_idx = N//2
        idx_list = [center_idx]

        twist_direction = -1
        twist_cnt = False
        twist_step = 1

        for i in range(1, N):
            next_idx = center_idx+twist_direction*twist_step
            idx_list.append(next_idx)

            twist_direction *= -1
            if twist_cnt:
                twist_step += 1
            twist_cnt = not twist_cnt

        return idx_list

    def generate(self, name):
        t_prep = 0
        if self.preparation:
            t_prep = self.TR/2
            self.seq.append({
                "t": 0,
                "type": "PULSE",
                "FA": self.FA/2,
            })
        if not self.k_center_first:
            self.readout_kY_idx = range(self.NFlip)
        else:
            self.readout_kY_idx = self.get_twisted_index(self.NFlip)
        for readout_idx, readout_kY in enumerate(self.readout_kY_idx):
            t_start = float(t_prep+self.TR*readout_idx)
            self.add_readout(
                t_start,
                self.FA*(((readout_idx % 2)*2-1) if self.sign_alter else 1),
                self.TR,
                self.GX,
                self.GY_max*(2*readout_kY/self.NFlip-1),
                readout_kY
            )
        with open(os.path.join("sequences_ssfp", name+".yaml"), "w") as f:
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
    ssfp = bSSFP(2.8, 10, [320, 320], [64, 64], 10, True, True, True)
    ssfp.generate("TR2.8_FA10_FOV320_K64_center_first")
    ssfp = bSSFP(2.8, 10, [320, 320], [64, 64], 10, False, True, True)
    ssfp.generate("TR2.8_FA10_FOV320_K64")
    ssfp = bSSFP(2.8, 20, [320, 320], [64, 64], 10, True, True, True)
    ssfp.generate("TR2.8_FA20_FOV320_K64_center_first")
    ssfp = bSSFP(2.8, 20, [320, 320], [64, 64], 10, False, True, True)
    ssfp.generate("TR2.8_FA20_FOV320_K64")
