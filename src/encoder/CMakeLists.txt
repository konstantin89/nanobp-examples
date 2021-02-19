cmake_minimum_required(VERSION 3.10.0)


set(ENCODER_SOURCES encoder.cpp ${NANOPB_SOURCES} ${NANOPB_AUTOGEN_SOURCES})

add_executable(encoder ${ENCODER_SOURCES})

target_include_directories(encoder PRIVATE ${INCLUDE_DIRECTORIES})

target_compile_features(encoder PRIVATE cxx_std_17)

