cmake_minimum_required(VERSION 3.10.0)

set(COMMON_LIB_SROUCES utils.cpp ${NANOPB_SOURCES})

add_library(common STATIC ${COMMON_LIB_SROUCES})

target_include_directories(common PRIVATE ${INCLUDE_DIRECTORIES})

target_compile_features(common PRIVATE cxx_std_17)
