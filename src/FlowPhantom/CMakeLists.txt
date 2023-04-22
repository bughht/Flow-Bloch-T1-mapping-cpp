# find_package(OpenMP)
project(FlowPhantom)
aux_source_directory(. DIR_LIB_SRCS)


add_library(FlowPhantom FlowPhantom.cpp FlowPhantom.h)
# target_link_libraries(FlowPhantom Eigen3::Eigen)
# target_link_libraries(FlowPhantom SeqLoader)
target_link_libraries(FlowPhantom M_voxel)
target_link_libraries(FlowPhantom OpenMP::OpenMP_CXX)