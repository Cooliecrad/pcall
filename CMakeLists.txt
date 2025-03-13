cmake_minimum_required(VERSION 3.10.0)

project(PCALL VERSION 1.0.0)

# 大量使用了宏，如果调试请打开保存中间文件
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps=obj")

include_directories(include)

# demo程序
add_executable(test demo/test_client.cpp
                    demo/test_server.cpp
                    demo/test.cpp)

# 模板库
add_library(client SHARED client/client.cpp)
target_include_directories(client PRIVATE client)

# 模板.C程序
add_executable(example_client client/cclient.c)
target_link_libraries(example_client PRIVATE client)