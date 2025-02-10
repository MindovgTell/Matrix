# General info
cmake_minimum_required(VERSION 3.27.5)

set(PROJECT_NAME Matrix)
project(${PROJECT_NAME} VERSION 1.1.0 )

# cpp options 
set(CMAKE_CXX_STANDARD 17) 

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")