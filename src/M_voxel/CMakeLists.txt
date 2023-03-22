project(M_voxel)
aux_source_directory(. DIR_LIB_SRCS)

set(SOURCE_FILES M_voxel.cpp M_voxel.h)

# add_library(M_voxel ${DIR_LIB_SRCS})
add_library(M_voxel ${SOURCE_FILES})
target_link_libraries (M_voxel Eigen3::Eigen)
target_link_libraries (M_voxel BlochSim)