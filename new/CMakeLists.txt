cmake_minimum_required(VERSION 3.16)
project(VM VERSION 0.1 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(./include)
add_subdirectory(vm)

