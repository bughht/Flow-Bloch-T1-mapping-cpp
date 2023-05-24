import yaml
import numpy as np
import os

gamma = 42.577478518e6  # MHz/T

class Pulse_SINC:
    def __init__(self,
                 FA,
                 slice_thickness,
                 pulse_bandwidth,
                 pulse_duration,
                 n_samples
                 ) -> None:
        self.seq=[]
        (self.FA,self.slice_thickness,self.pulse_bandwidth,self.pulse_duration,self.n_samples)=(FA,slice_thickness,pulse_bandwidth,pulse_duration,n_samples)
        self.data_process()

    def data_process(self):
        self.G0=self.pulse_bandwidth/(gamma*self.slice_thickness)

if __name__ == "__main__":
    sinc=Pulse_SINC(FA=30,slice_thickness=5,pulse_bandwidth=1000,pulse_duration=0.5,n_samples=100)