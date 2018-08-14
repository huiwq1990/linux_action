cmake_minimum_required(VERSION 3.9)
project(linux_action C)

set(CMAKE_C_STANDARD 99)

add_executable(demo_tcp_server tcp/demo_tcp_server.c)
add_executable(demo_tcp_client tcp/demo_tcp_client.c)
add_executable(readwrite_demo io/readwrite_demo.c)
add_executable(mmap_demo1 mmap/mmap_demo.c)