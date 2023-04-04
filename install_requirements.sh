# mkdir Downloads
# cd Downloads

# # Install Eigen
# sudo apt install libeigen3-dev

# Install Yaml-cpp
# wget https://github.com/jbeder/yaml-cpp/archive/refs/tags/yaml-cpp-0.7.0.zip -O yaml-cpp-0.7.0.zip
# unzip yaml-cpp-0.7.0.zip
# cd yaml-cpp-yaml-cpp-0.7.0
# mkdir build 
# cd build
# cmake -DBUILD_SHARED_LIBS=ON ..
# sudo make install

# # Install tqdm-cpp
# cd ../..
# git clone https://gitlab.com/miguelraggi/tqdm-cpp.git
# cp tqdm-cpp/tqdm.hpp  ../include/tqdm.hpp