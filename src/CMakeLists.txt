cmake_minimum_required(VERSION 3.10.0)


set(INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR} ${NANOPB_INCLUDE_PATH})

FILE (GLOB_RECURSE NANOPB_AUTOGEN_SOURCES ${CMAKE_CURRENT_LIST_DIR}/auto_generated/*.c)

add_subdirectory(common)

add_subdirectory(encoder)
add_subdirectory(decoder)

#set(COMPILE_PROTO_SCRIPT_PATH  ${CMAKE_CURRENT_LIST_DIR}/../compile_proto.bat)

#add_custom_command(TARGET encoder PRE_BUILD
#                   COMMAND ${COMPILE_PROTO_SCRIPT_PATH})

#add_custom_command(TARGET decoder PRE_BUILD
#                   COMMAND ${COMPILE_PROTO_SCRIPT_PATH})