cmake_minimum_required(VERSION 3.10)

project(vm01 C)

file(GLOB SOURCES "*.c")
add_executable(vm01 ${SOURCES})
