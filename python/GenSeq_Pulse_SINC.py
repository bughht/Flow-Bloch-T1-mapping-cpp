import yaml
import numpy as np
import os

gamma = 42.577478518e6  # MHz/T

class Pulse_SINC:
    def __init__(self,
                 FA,
                 slice_thickness, # mm
                 pulse_bandwidth, # Hz
                 pulse_duration, # ms
                 n_samples
                 ) -> None:
        self.seq=[]
        (self.FA,self.slice_thickness,self.pulse_bandwidth,self.pulse_duration,self.n_samples)=(FA,slice_thickness,pulse_bandwidth,pulse_duration,n_samples)
        self.data_process()

    def data_process(self):
        self.G0=self.pulse_bandwidth/(gamma*self.slice_thickness) # mT/m
        self.t0=1/self.pulse_bandwidth
        self.t_sample=np.linspace(-self.pulse_duration/2,self.pulse_duration/2,self.n_samples)
        self.sinc=np.sinc(np.pi*self.t_sample/self.t0/1000)

if __name__ == "__main__":
    sinc=Pulse_SINC(FA=30,slice_thickness=8,pulse_bandwidth=3246,pulse_duration=0.8,n_samples=2000)

    import matplotlib.pyplot as plt

    plt.plot(np.linspace(-sinc.pulse_duration/2,sinc.pulse_duration/2,sinc.n_samples),sinc.sinc)
    plt.show()
    