project(calmk)

#set(CMAKE_VERBOSE_MAKEFILE ON)
#set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

aux_source_directory(. DIR_SRC)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(calmk test_config.cc)

target_link_libraries(calmk CALMK_LIB)

set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/../bin)
set(LIBRARY_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/../lib)