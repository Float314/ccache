cmake_minimum_required(VERSION 3.15)
project(ccacheparser VERSION 0.1.0 LANGUAGES CXX) # Insert project name here

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
) # Add files as they expand

target_compile_features(${PROJECT_NAME}
    INTERFACE )