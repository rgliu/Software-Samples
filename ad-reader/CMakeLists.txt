cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-std=c++14")

project(adProject)

add_executable(
	adProject
	main.cpp
	RequestReader.cpp
	AdFile.cpp
	AdSpec.cpp
)