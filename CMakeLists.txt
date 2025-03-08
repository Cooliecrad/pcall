cmake_minimum_required(VERSION 3.10.0)

project(PCODE VERSION 1.0.0)

add_library(pcall pcall.cpp)

# 测试1：PCall
add_executable(pcall_test pcall_test.cpp)
target_link_libraries(pcall_test pcall)
