cmake_minimum_required(VERSION 3.26)
project(tree_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(tree_cpp main.cpp
        render.cpp
        render.h
        tree.cpp
        tree.h
        task.cpp
        task.h)

set(GRAPHVIZ_DIR "/opt/homebrew/Cellar/graphviz/9.0.0")
file(GLOB GVC_LIBS "${GRAPHVIZ_DIR}/lib/*.dylib")
target_link_libraries(${CMAKE_PROJECT_NAME} ${GVC_LIBS})
include_directories("${GRAPHVIZ_DIR}/include/graphviz")
