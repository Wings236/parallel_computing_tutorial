cmake_minimum_required(VERSION 3.12)

project(SimpleCPPCNN)

# OpenCV
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

aux_source_directory(./src DIR_SRCS)

include_directories(./include)

add_executable(SimpleCPPCNN ${DIR_SRCS})

target_include_directories(SimpleCPPCNN PRIVATE ${OpenCV_INCLUDE_DIRS})

target_link_libraries(SimpleCPPCNN ${OpenCV_LIBS})