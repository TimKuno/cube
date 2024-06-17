cmake_minimum_required(VERSION 3.28)
project(Cube)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DMY_DEBUG_FLAG")

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory(src)

add_executable(Cube src/main.cpp)

target_link_libraries(Cube
        PRIVATE
        ${SDL2_LIBRARIES}
        OpenGL::GL
        GLEW::GLEW
        renderer
        utils
)
#target_link_libraries(Cube PRIVATE renderer)
target_include_directories(Cube
        PUBLIC
        ${SDL2_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
)