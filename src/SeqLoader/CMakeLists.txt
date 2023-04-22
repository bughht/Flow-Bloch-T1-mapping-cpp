project(SeqLoader)
aux_source_directory(. DIR_LIB_SRCS)

set(SOURCE_FILES 
    SeqLoader.cpp
    SeqLoader.h)

add_library(SeqLoader SeqLoader.cpp SeqLoader.h)
target_link_libraries(SeqLoader yaml-cpp)