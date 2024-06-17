add_library(renderer STATIC
        vertex_buffer.cpp
        vertex_buffer.h
        shader.cpp
        shader.h
)

target_link_libraries(renderer
        PUBLIC
        utils
)