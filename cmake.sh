cd build
# cmake .. \
cmake -DCMAKE_PREFIX_PATH=/home/honght/libtorch ..
# -DPYTHON_INCLUDE_DIR=$(python -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())")  \
# -DPYTHON_LIBRARY=$(python -c "import distutils.sysconfig as sysconfig; print(sysconfig.get_config_var('LIBDIR'))") \
# -DPYTHON3_INCLUDE_DIRS=$(python -c "from distutils.sysconfig import get_python_inc; print(get_python_inc())")  \
# -DPYTHON3_LIBRARIES=$(python -c "import distutils.sysconfig as sysconfig; print(sysconfig.get_config_var('LIBDIR'))") \
# -DNumPy_INCLUDE_DIRS=$(/home/honght/miniconda3/envs/NUMERICAL/lib/python3.7/site-packages/numpy/core/include)


make