cmake_minimum_required(VERSION 3.12)

project(SimpleCPPCNN)

aux_source_directory(./src DIR_SRCS)

include_directories(./include)

add_executable(SimpleCPPCNN ${DIR_SRCS})