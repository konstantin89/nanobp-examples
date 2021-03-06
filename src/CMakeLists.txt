cmake_minimum_required(VERSION 3.10.0)


set(INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR} ${NANOPB_INCLUDE_PATH})

FILE (GLOB_RECURSE NANOPB_AUTOGEN_SOURCES ${CMAKE_CURRENT_LIST_DIR}/auto_generated/*.c)

add_subdirectory(common)

add_subdirectory(encoder)

add_subdirectory(decoder)

