project(BlochSim)
aux_source_directory(. DIR_LIB_SRCS)

set(SOURCE_FILES 
    BlochSim.cpp
    BlochSim.h)

# add_library(BlochSim ${DIR_LIB_SRCS})
add_library(BlochSim ${SOURCE_FILES})
target_link_libraries (BlochSim Eigen3::Eigen)
# target_link_libraries (BlochSim "${TORCH_LIBRARIES}")