cmake_minimum_required(VERSION 3.28)
project(Cube)

set(CMAKE_CXX_STANDARD 20)
add_compile_definitions(NDEBUG)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)

add_subdirectory(src)

add_executable(Cube src/main.cpp)

target_link_libraries(Cube
        PRIVATE
        ${SDL2_LIBRARIES}
        OpenGL::GL
        GLEW::GLEW
        glm::glm
        renderer
        utils
)

target_include_directories(Cube
        PUBLIC
        ${SDL2_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
)