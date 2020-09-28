aux_source_directory(. DIR_LIB_SRC)

#set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(CALMK_LIB ${DIR_LIB_SRC})
