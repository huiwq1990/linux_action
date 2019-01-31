cmake_minimum_required(VERSION 3.8)
project(debugger_demo)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(debugger_demo ${SOURCE_FILES})