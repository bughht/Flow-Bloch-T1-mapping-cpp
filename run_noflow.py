from subprocess import run
from multiprocessing import Process
import numpy as np

run("rm -rf nohup.out", shell=True)
run("mkdir log", shell=True)
# run("build/src/T1-Mapping -h", shell=True)

# T1_Blood = np.arange(1400, 2001, 100).tolist()
# T1_Blood = np.linspace(1000, 2000, 25)
T1_Blood = 1500
T2_Blood = 50

T1_Tissue = 1000
T2_Tissue = 50

n_vessel_x = 1
n_vessel_y = 1

vessel_radius = 64

n_particle = int(1e5)

# seq_path = "sequences_MOLLI/MOLLI_533_TR2.8_FA35_FOV256_K64_thick8_dt20_center_first.yaml"
# seq_path = "sequences_MOLLI/MOLLI_533_TR2.8_FA35_FOV256_K64_thick8_dt20.yaml"
seq_path = "sequences_MOLLI/MOLLI_533_TR2.8_FA35_FOV256_K64_thick8_Gz_dt20.yaml"

# flow_speed_fast = np.linspace(0, 1, 16).astype(str)
# flow_speed_slow = np.linspace(0, 0.01, 16).astype(str)

flow_speed = 0
fs = [str(flow_speed) for _ in range(n_vessel_x * n_vessel_y)]
# flow_speed = np.linspace(0, 0.01, 1 * n_vessel_x * n_vessel_y).reshape(
#     1, n_vessel_x * n_vessel_y).astype(str)
# flow_speed = np.linspace(0, 0.01, 1 * 16).reshape(1, 16).astype(str)
# flow_speed = np.linspace(0.9, 1.0, 16).reshape(1, 16).astype(str)
# flow_speed = np.linspace(0.15, .17, 16).reshape(1, 16).astype(str)

space = [256, 256, 4]
_space = [str(S) for S in space]


def execute_cmd(cmd, idx):
    # run(cmd + " > log/EXP_id{}.log".format(idx), shell=True)
    run(cmd, shell=True)
    # print(cmd)


exp_idx = 0
# _T1_blood = [str(_) for _ in T1_Blood]
# _T2_blood = [str(T2_Blood) for _ in range(n_vessel_x * n_vessel_y)]
_T1_blood = str(T1_Blood)
_T2_blood = str(T2_Blood)
_T1_tissue = T1_Tissue
_T2_tissue = T2_Tissue

# save_path = "exp_result_fast/ID{}_Speed_min{}_max{}".format(
# save_path = "exp_result_slow_1400_5x5/ID{}_Speed_min{}_max{}".format(
#     # save_path = "exp_result/ID{}_Speed_min{}_max{}".format(
#     exp_idx,
#     fs[0],
#     fs[-1])
save_path = "experiments/exp_MOLLI_no_flow"
exp_exec = "build/src/T1-Mapping --T1_Blood {} --T2_Blood {} --T1_Tissue {} --T2_Tissue {} --n_vessel_xy {} {} --vessel_radius {} --n_particle {} --seq_path {} --save_path {} --flow_speed {} --space {}".format(
    " ".join(_T1_blood), " ".join(_T2_blood), _T1_tissue, _T2_tissue,
    n_vessel_x, n_vessel_y, vessel_radius, n_particle, seq_path, save_path,
    " ".join(fs), " ".join(_space))
print(exp_exec)
execute_cmd(exp_exec, exp_idx)
# p = Process(target=execute_cmd, args=(exp_exec, exp_idx,))
# p.start()
