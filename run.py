from subprocess import run
from multiprocessing import Process
import numpy as np

run("build/src/T1-Mapping -h", shell=True)

# T1_Blood = np.arange(1400, 2001, 100).tolist()
T1_Blood = np.linspace(1400, 2000, 7)
T2_Blood = 50

T1_Tissue = 1000
T2_Tissue = 50

n_vessel_x = 4
n_vessel_y = 4

vessel_radius = 25

n_particle = 100000000

seq_path = "sequences_MOLLI/MOLLI_533_TR2.8_FA35_FOV256_K64_thick8_center_first.yaml"

flow_speed_fast = np.linspace(0, 1, 16).astype(str)
flow_speed_slow = np.linspace(0, 0.01, 16).astype(str)


def execute_cmd(cmd):
    run(cmd, shell=True)
    # print(cmd)


for exp_idx, T1 in enumerate(T1_Blood):
    _T1_blood = [str(T1) for _ in range(n_vessel_x * n_vessel_y)]
    _T2_blood = [str(T2_Blood) for _ in range(n_vessel_x * n_vessel_y)]
    _T1_tissue = T1_Tissue
    _T2_tissue = T2_Tissue

    save_path_slow = "exp_result/ID{}_T1{}_slow".format(exp_idx, T1)
    save_path_fast = "exp_result/ID{}_T1{}_fast".format(exp_idx, T1)
    execute_cmd_slow = "build/src/T1-Mapping --T1_Blood {} --T2_Blood {} --T1_Tissue {} --T2_Tissue {} --n_vessel_xy {} {} --vessel_radius {} --n_particle {} --seq_path {} --save_path {} --flow_speed {} ".format(
        " ".join(_T1_blood), " ".join(_T2_blood), _T1_tissue, _T2_tissue,
        n_vessel_x, n_vessel_y, vessel_radius, n_particle, seq_path,
        save_path_slow, " ".join(flow_speed_slow))
    execute_cmd_fast = "build/src/T1-Mapping --T1_Blood {} --T2_Blood {} --T1_Tissue {} --T2_Tissue {} --n_vessel_xy {} {} --vessel_radius {} --n_particle {} --seq_path {} --save_path {} --flow_speed {} ".format(
        " ".join(_T1_blood), " ".join(_T2_blood), _T1_tissue, _T2_tissue,
        n_vessel_x, n_vessel_y, vessel_radius, n_particle, seq_path,
        save_path_fast, " ".join(flow_speed_fast))
    p_slow = Process(target=execute_cmd, args=(execute_cmd_slow, ))
    p_fast = Process(target=execute_cmd, args=(execute_cmd_fast, ))
    p_slow.start()
    p_fast.start()
