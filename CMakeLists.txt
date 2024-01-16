cmake_minimum_required(VERSION 3.0)
project(LockFree)

# 设置C++标准为C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置Debug模式
set(CMAKE_BUILD_TYPE Debug)

# 添加子目录
add_subdirectory(queue)