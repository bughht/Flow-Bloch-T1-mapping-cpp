cmake_minimum_required(VERSION 3.0.0)
project(Flow-Bloch-T1-mapping VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
find_package(PythonLibs 3.0 REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(yaml-cpp REQUIRED)
find_package( OpenCV REQUIRED )

include_directories(${PYTHON3_INCLUDE_DIRS} ${NumPy_INCLUDE_DIRS})
include_directories(SYSTEM ${matplotlib_SOURCE_DIR})
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories($(PROJECT_SOURCE_DIR)/src/BlochSim)
include_directories($(PROJECT_SOURCE_DIR)/src/M_voxel)
include_directories($(PROJECT_SOURCE_DIR)/src/SeqSimulator)
include_directories($(PROJECT_SOURCE_DIR)/src/SeqLoader)
include_directories($(PROJECT_SOURCE_DIR)/include)


add_subdirectory(src)
add_subdirectory(test)
