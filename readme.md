# T1 mapping Bloch Simulator

## Introduction

This is a C++ implementation of the Bloch simulator for T1 mapping. It includes the following modules: 

- Bloch simulation
- b-SSFP sequence generation and simulation
    - k-space sampling and image reconstruction
- MOLLI sequence generation and simulation
- Flow phantom simulation
- T1 fitting

This project was originally transplanted from [FLOW-BLOCH-T1-MAPPING](https://github.com/bughht/Flow-Bloch-T1-mapping) for higher performance. Now it's a standalone project.


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

## Features

- Sequence generator and T1-fitting are implemented in **Python** with **Numpy** and **Scipy**. 
- The sequence simulator is implemented in **C++** for higher performance.
- Matrix computation in Bloch simulation is accelerated by **Eigen3**.
- Parallel computation in k-space sampling and flow phantom simulation is accelerated by **OpenMP**.
- **OpenCV** is used for MRI image reconstruction. 

## Prerequisites

- CMake >= 3.0
    - OpenCV
    - Eigen3
    - OpenMP >= 4.5.0
- Python >= 3.7
    - numpy
    - scipy
    - matplotlib
    - pyyaml
    - ruamel.yaml
    - tqdm
    - ipynbcompress (Please build from [personal manipulated source](https://github.com/bughht/ipynbcompress-plus))


## Build and Run

```bash
mkdir build
./cmake.sh
# Please set the parameters in run.py first.
# The default parameters are designed for experiments server with at least 32 processors and 64GB memory.
python run.py
```

## TODO

- [x] Bloch Simulation
- [x] MOLLI sequence simulation
- [x] K-space sampling & reconstruction
- [x] Flow simulation
- [x] Data Collection & Analysis
- [x] Paper

## License: [GPL-2.0](LICENSE)

    FLOW-BLOCH-T1-MAPPING
    Copyright (C) 2023  Haotian Hong

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
