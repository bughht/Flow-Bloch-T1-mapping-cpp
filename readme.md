# T1 mapping Bloch Simulator

## Introduction

This is a C++ implementation of the Bloch simulator for T1 mapping. It includes the following modules: 

- Bloch simulation
- b-SSFP sequence generation and simulation
    - k-space sampling and image reconstruction
- MOLLI sequence generation and simulation
- Flow phantom simulation
- T1 fitting

This project was originally transplanted from [FLOW-BLOCH-T1-MAPPING](https://github.com/bughht/Flow-Bloch-T1-mapping) for higher simulation performance. Now it's a standalone project.



## Project Structure

- `src` contains the source code of the simulator.
    - `BlochSim` contains the Bloch simulation code.
    - `FlowPhantom` contains the flow phantom simulation code.
    - `M_voxel` contains the magnetization vector class.
    - `SeqLoader` contains the sequence loader code.
    - `SeqSimulator` contains the sequence simulator code.
    - `main.cpp` is the main function.
- `python` contains the python scripts.
    - `GenSeq_MOLLI.py` generates the MOLLI sequence.
    - `GenSeq_SSFP.py` generates the b-SSFP readout sequence.
    - `load_cppimg.py` loads the image generated by the simulator.
    - `MOLLI_fit.py` contains the fit algorithm.
    - `T1_fit.ipynb` fits the T1 data and display the result.
- `test` contains the test code.
- `build` is the build directory, executables will be generated here.
- `run.py` enables parallel execution of the simulator, temporarly for experiments.

```bash
FLOW-BLOCH-T1-MAPPING-CPP
├── build.sh
├── build_run.sh
├── build
│   ├── ...
├── cmake.sh
├── include
│   ├── argparse.hpp
│   └── tqdm.hpp
├── install_requirements.sh
├── python
│   ├── GenSeq_MOLLI.py
│   ├── GenSeq_SSFP.py
│   ├── load_cppimg.py
│   ├── MOLLI_fit.py
│   └── T1_fit.ipynb
├── run.py
├── src
│   ├── BlochSim
│   │   ├── BlochSim.cpp
│   │   ├── BlochSim.h
│   │   └── CMakeLists.txt
│   ├── CMakeLists.txt
│   ├── FlowPhantom
│   │   ├── CMakeLists.txt
│   │   ├── FlowPhantom.cpp
│   │   └── FlowPhantom.h
│   ├── main.cpp
│   ├── M_voxel
│   │   ├── CMakeLists.txt
│   │   ├── M_voxel.cpp
│   │   └── M_voxel.h
│   ├── SeqLoader
│   │   ├── CMakeLists.txt
│   │   ├── SeqLoader.cpp
│   │   └── SeqLoader.h
│   └── SeqSimulator
│       ├── CMakeLists.txt
│       ├── SeqSimulator.cpp
│       └── SeqSimulator.h
└── test
    ├── CMakeLists.txt
    ├── test_BlochSim.cpp
    ├── test_bSSFP.cpp
    ├── test_FlowPhantom.cpp
    ├── test_matplotlib.cpp
    ├── test_opencv.cpp
    └── test_yaml.cpp
```

## Requirements

- CMake >= 3.0
- C++ >= 17
- OpenCV
- Eigen3
- OpenMP
<!-- - Yaml-cpp
- tqdm-cpp -->

## Usage

```bash
mkdir build
./cmake.sh
python run.py
```

## TODO

- [x] Bloch Simulation
- [x] MOLLI sequence simulation
- [x] K-space sampling & reconstruction
- [x] Flow simulation
- [ ] Data Collection & Analysis
- [ ] Paper

## License

The project Flow-Bloch-T1-mapping-cpp is available under the [MIT license](https://github.com/bughht/Flow-Bloch-T1-mapping-cpp/blob/master/LICENSE).
