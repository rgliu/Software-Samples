cmake_minimum_required(VERSION 3.0.0...3.5)
project(XanderOne VERSION 0.1.0)

add_subdirectory(proclib)

add_executable(XanderOne main.cpp)
target_link_libraries(XanderOne ProcLib)
