cmake_minimum_required(VERSION 3.10.0)

set(DECODER_SOURCES decoder.cpp ${NANOPB_SOURCES} ${NANOPB_AUTOGEN_SOURCES})

add_executable(decoder ${DECODER_SOURCES})

target_include_directories(decoder PRIVATE ${INCLUDE_DIRECTORIES})

target_compile_features(decoder PRIVATE cxx_std_17)
