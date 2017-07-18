cmake_minimum_required(VERSION 3.5)

project(IntroFEM)
set (CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

message(${EIGEN3_INCLUDE_DIR})

add_executable(main main.cpp)

