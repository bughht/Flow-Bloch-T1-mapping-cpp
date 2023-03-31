import yaml
import os
import numpy as np


class MOLLI:
    def __init__(
        self,
        reverse_t=[0, 8000],
        readout_t=[100, 1100, 2100, 3100, 4100, 8200, 9200, 10200],
        readout_seq="bSSFP_TR2.8_FA25_N75_SA",
        dt=None
    ):
        '''
        reverse_t: list of time points for reverse readout
        readout_t: list of time points for readout
        readout_seq: name of readout sequence
        dt: time step for free precession simulation
        '''
        self.reverse_t = np.asarray(reverse_t)
        self.readout_t = np.asarray(readout_t)
        self.load_readout(readout_seq=readout_seq)
        self.seq = list()
        self.dt = dt
        self.process_seq()

    def process_seq(self):
        self.readout_end_t = self.readout_time+self.readout_t
        seq_t = np.concatenate(
            (self.reverse_t, self.readout_t, self.readout_end_t))
        label_reverse = ["PULSE"]*len(self.reverse_t)
        label_readout_start = ["READOUT_START"]*len(self.readout_t)
        label_readout_end = ["READOUT_END"]*len(self.readout_end_t)
        label = np.concatenate(
            (label_reverse, label_readout_start, label_readout_end))
        seq_t_idx = np.argsort(seq_t)
        self.seq_t = seq_t[seq_t_idx]
        self.label = label[seq_t_idx]
        if self.dt is not None:
            dt_t = []
            for i, (t, l) in enumerate(zip(self.seq_t, self.label)):
                if i < len(self.seq_t)-1:
                    if l != "READOUT_START":
                        for dt_idx in range(1, int((self.seq_t[i+1]-t)//self.dt)):
                            dt_t.append(t+dt_idx*self.dt)
            label_dt = ["NONE"]*len(dt_t)
            self.seq_t = np.concatenate((self.seq_t, dt_t))
            self.label = np.concatenate((self.label, label_dt))
            seq_idx = np.argsort(self.seq_t)
            self.seq_t = self.seq_t[seq_idx]
            self.label = self.label[seq_idx]

        print(self.seq_t)
        print(self.label)

        # if self.dt is not None:

    def load_readout(self, readout_seq):
        # Load readout sequence
        with open(os.path.join("sequences_ssfp", readout_seq+".yaml"), "r") as f:
            self.readout_seq = yaml.load(
                f, Loader=yaml.FullLoader)
        self.readout_time = self.readout_seq[-1]["t"]

    def generate(self, name):
        # Generate sequence
        for label, t in zip(self.label, self.seq_t):
            TS = {
                "type": str(label),
                "t": float(t)
            }
            if label == "PULSE":
                TS["FA"] = 180
            self.seq.append(TS)
            if label == "READOUT_START":
                for TS_readout in self.readout_seq:
                    s = TS_readout.copy()
                    s["t"] += float(t)
                    self.seq.append(s)
        with open(os.path.join("sequences_MOLLI", name+".yaml"), "w") as f:
            yaml.dump(self.seq, f)


if __name__ == "__main__":
    # molli = MOLLI(readout_seq="TR2.8_FA20_FOV320_K64_center_first", dt=1)
    # molli.generate("MOLLI_533_dt_TR2.8_FA20_FOV320_K64_center_first")
    # molli = MOLLI(readout_seq="TR2.8_FA20_FOV320_K64_center_first")
    # molli.generate("MOLLI_533_TR2.8_FA20_FOV320_K64_center_first")
    molli = MOLLI(readout_seq="TR2.8_FA10_FOV320_K64_center_first")
    molli.generate("MOLLI_533_TR2.8_FA10_FOV320_K64_center_first")
