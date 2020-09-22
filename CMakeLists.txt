cmake_minimum_required(VERSION 2.8)

project(calmk)

set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

add_subdirectory(./src)
add_subdirectory(./test)

include_directories(./include)

