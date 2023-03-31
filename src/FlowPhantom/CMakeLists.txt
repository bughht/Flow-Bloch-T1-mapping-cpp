project(FlowPhantom)

set(SOURCE_FILES FlowPhantom.cpp FlowPhantom.h)

add_library(FlowPhantom ${SOURCE_FILES})
target_link_libraries(FlowPhantom Eigen3::Eigen)
target_link_libraries(FlowPhantom M_voxel)