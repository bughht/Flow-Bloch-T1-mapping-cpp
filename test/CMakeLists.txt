# include_directories($(PROJECT_SOURCE_DIR)/include)

# find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
# find_package(Python3 COMPONENTS NumPy)

add_executable(test_BlochSim test_BlochSim.cpp )
add_executable(test_yaml test_yaml.cpp )
add_executable(test_matplotlib test_matplotlib.cpp )
add_executable(test_opencv test_opencv.cpp )
add_executable(test_bSSFP test_bSSFP.cpp )
add_executable(test_FlowPhantom test_FlowPhantom.cpp )

target_link_libraries(test_BlochSim BlochSim)
target_link_libraries(test_yaml SeqLoader)
# target_link_libraries(test_matplotlib
#         ${Python3_LIBRARIES}
#         Python3::NumPy
# )
target_link_libraries(test_opencv ${OpenCV_LIBS})
target_link_libraries(test_bSSFP BlochSim)
target_link_libraries(test_bSSFP SeqLoader)
target_link_libraries(test_bSSFP M_voxel)
target_link_libraries(test_bSSFP SeqSimulator)
target_link_libraries(test_FlowPhantom M_voxel)
target_link_libraries(test_FlowPhantom BlochSim)
# target_link_libraries(test_bSSFP 
#     ${Python3_LIBRARIES}
#     Python3::NumPy
# )

