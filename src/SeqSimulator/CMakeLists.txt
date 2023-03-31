project(SeqSimulator)
aux_source_directory(. DIR_LIB_SRCS)

add_library(SeqSimulator ${DIR_LIB_SRCS})
target_link_libraries(SeqSimulator Eigen3::Eigen)
target_link_libraries(SeqSimulator BlochSim)
target_link_libraries(SeqSimulator FlowPhantom)
# target_link_libraries(SeqSimulator
#     ${PYTHON_LIBRARIES}
#     Python3::NumPy
# )
target_link_libraries(SeqSimulator ${OpenCV_LIBS}) 