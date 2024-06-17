#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLE
#include <SDL2/SDL.h>

#include "utils/data_types.h"
#include "renderer/vertex_buffer.h"
#include "renderer/shader.h"

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetSwapInterval(1);

    SDL_Window* window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
        SDL_WINDOW_OPENGL);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    GLenum err = glewInit();
    if(err != GLEW_OK) {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        return -1;
    }
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    Vertex vertices[] = {
        Vertex{-0.5f, -0.5f, 0.0f,
        1.0f, 0.0f, 0.0f, 1.0f},
        Vertex{0.0f, 0.5f, 0.0f,
        0.0, 1.0f, 0.0f, 1.0f},
        Vertex{0.5f, -0.5f, 0.0f,
        0.0f, 0.0f, 1.0f, 1.0f}
    };
    uint32 numVertices = 3;

    VertexBuffer vertexBuffer(vertices, numVertices);
    vertexBuffer.unbind();

    Shader shader("../shaders/basic.vert", "../shaders/basic.frag");
    shader.bind();


    bool close = false;
    while (!close) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                close = true;
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vertexBuffer.bind();
        glDrawArrays(GL_TRIANGLES, 0, numVertices);
        vertexBuffer.unbind();

        SDL_GL_SwapWindow(window);
    }

    return 0;
}
