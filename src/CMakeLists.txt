project(T1-Mapping)
include_directories($(PROJECT_SOURCE_DIR)/include)
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(Python3 COMPONENTS NumPy)

aux_source_directory(. DIR_SRCS)

add_subdirectory(BlochSim)
add_subdirectory(SeqLoader)
add_subdirectory(M_voxel)
add_subdirectory(SeqSimulator)

add_executable(T1-Mapping main.cpp)

target_link_libraries(T1-Mapping BlochSim)
target_link_libraries(T1-Mapping SeqLoader)
target_link_libraries(T1-Mapping M_voxel)
target_link_libraries(T1-Mapping SeqSimulator)
target_link_libraries(T1-Mapping 
    ${PYTHON_LIBRARIES}
    Python3::NumPy
)


