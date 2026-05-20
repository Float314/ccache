cmake_minimum_required(VERSION 3.14)

# Define the project name and version
project(ccacheparser
    VERSION 1.0.0 
    LANGUAGES CXX
)

add_library(ccache INTERFACE)

target_include_directories(ccache INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(ccache INTERFACE cxx_std_23)
