cmake_minimum_required(VERSION 3.12)

project(OpenCVMatrix)

aux_source_directory(./src DIR_SRCS)

include_directories(./include)

add_executable(OpenCVMatrix ${DIR_SRCS})