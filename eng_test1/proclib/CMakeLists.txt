cmake_minimum_required(VERSION 3.0.0...3.5)
project(ProcLib VERSION 0.1.0)


add_library(ProcLib ${CMAKE_CURRENT_SOURCE_DIR}/source/testlib.cpp)
target_include_directories(ProcLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
