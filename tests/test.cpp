// test file

#include <iostream>
#include "ccache.hpp"

int main() {
    std::string testString = R"(CMAKE_BUILD_TYPE:STRING=Debug
# This is a comment 
# Hi ig
CMAKE_C_COMPILER:FILEPATH=/usr/bin/cc
CMAKE_CXX_COMPILER:FILEPATH=/usr/bin/c++
)";
    
    CMakeCacheParse::parse parser(testString);
    
    std::cout << "Build Type: " << parser["CMAKE_BUILD_TYPE"]->fetch() << std::endl;
    std::cout << "C Compiler: " << parser["CMAKE_C_COMPILER"]->fetch() << std::endl;
    std::cout << "C++ Compiler: " << parser["CMAKE_CXX_COMPILER"]->fetch() << std::endl;
    std::cout << "CMAKE_BUILD_TYPE Type: " << parser["CMAKE_BUILD_TYPE"]->type() << std::endl;
    
    return 0;
}