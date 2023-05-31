import numpy as np
import matplotlib.pyplot as plt

gamma = 42.577478518e6  # MHz/T
bandwidth=3246 # Hz
thickness=8 #mm
n_sample=int(2e2)

G=bandwidth/(gamma*thickness) # mT/m

t=np.linspace(-0.4,0.4,n_sample)
t0=1e3/bandwidth # ms

rf=np.sinc(np.pi*t/t0)

n_M=64
M=np.zeros((3,n_M))
pos=np.linspace(-thickness,thickness,n_M)

def free_precession(dt,T1,T2,df):
    phi=2*np.pi*df*dt/1000
    E1=np.exp(-dt/T1)
    E2=np.exp(-dt/T2)
    A=np.asarray([[E2,0,0],[0,E2,0],[0,0,E1]])
    B=np.array([[0],[0],[1-E1]])
    return A,B

def Rx(phi):
    return np.array([[np.cos(phi),-np.sin(phi),0],[np.sin(phi),np.cos(phi),0],[0,0,1]])

for i in range(n_M):
    M[2,i]=1

for i in range(n_M):
    for p in rf:
        A,B=free_precession(t[1]-t[0],1500,50,0)
        M[:,i]=A@M[:,i]+B
        


