cmake_minimum_required(VERSION 3.10.0)


set(COMPILE_PROTO_SCRIPT_PATH  ${CMAKE_CURRENT_LIST_DIR}/../compile_proto.bat)

# TODO - compile nanopb in lib
FILE (GLOB_RECURSE NANOPB_SOURCES ${CMAKE_CURRENT_LIST_DIR}/nanopb/*.c)

FILE (GLOB_RECURSE NANOPB_AUTOGEN_SOURCES ${CMAKE_CURRENT_LIST_DIR}/auto_generated/*.c)

set(ENCODER_SOURCES encoder.cpp ${NANOPB_SOURCES} ${NANOPB_AUTOGEN_SOURCES})
add_executable(encoder ${ENCODER_SOURCES})

set(DECODER_SOURCES decoder.cpp ${NANOPB_SOURCES} ${NANOPB_AUTOGEN_SOURCES})
add_executable(decoder ${DECODER_SOURCES})

set(INCLUDE_DIRECTORIES . nanopb auto_generated)

target_include_directories(encoder PRIVATE ${INCLUDE_DIRECTORIES})

target_include_directories(decoder PRIVATE ${INCLUDE_DIRECTORIES})


#add_custom_command(TARGET encoder PRE_BUILD
#                   COMMAND ${COMPILE_PROTO_SCRIPT_PATH})

#add_custom_command(TARGET decoder PRE_BUILD
#                   COMMAND ${COMPILE_PROTO_SCRIPT_PATH})