# include_directories($(PROJECT_SOURCE_DIR)/include)

# find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
# find_package(Python3 COMPONENTS NumPy)

add_executable(test_BlochSim test_BlochSim.cpp )
add_executable(test_yaml test_yaml.cpp )
add_executable(test_matplotlib test_matplotlib.cpp )

target_link_libraries(test_BlochSim BlochSim)
target_link_libraries(test_yaml SeqLoader)
target_link_libraries(test_matplotlib
    PRIVATE
        ${PYTHON_LIBRARIES}
        Python3::NumPy
)

