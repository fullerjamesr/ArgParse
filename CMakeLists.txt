cmake_minimum_required(VERSION 3.6)
project(ArgParse)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D__USE_MINGW_ANSI_STDIO=1")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -flto")

set(SOURCE_FILES argparse.c argparse.h)
add_library(argparse ${SOURCE_FILES})
add_executable(test_argparse ${SOURCE_FILES} test_argparse.c)