cmake_minimum_required(VERSION 3.10)

project(CLI_Calculator C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(CLI_Calculator main.c)

# 🔑 Link math library
target_link_libraries(CLI_Calculator m)
