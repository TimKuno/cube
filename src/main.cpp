#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLE
#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils/data_types.h"
#include "renderer/vertex_buffer.h"
#include "renderer/index_buffer.h"
#include "renderer/shader.h"

#ifdef NDEBUG
void openGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    std::cout << "[OpenGL Error] " << message << std::endl;
}
#endif

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetSwapInterval(1);

#ifdef NDEBUG
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

    int width = 800;
    int height = 600;
    SDL_Window* window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
        SDL_WINDOW_OPENGL);
    SDL_GL_CreateContext(window);

    GLenum err = glewInit();
    if(err != GLEW_OK) {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        return -1;
    }
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

#ifdef NDEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(openGLDebugCallback, nullptr);
#endif

    Vertex vertices[] = {
        // Red side
        Vertex{-0.5f, -0.5f, -0.5f,
        1.0f, 0.f, 0.0f, 1.0f},
        Vertex{0.5f, -0.5f, -0.5f,
        1.0f, 0.0f, 0.0f, 1.0f},
        Vertex{0.5f,  0.5f, -0.5f,
        1.0f, 0.0f, 0.0f, 1.0f},
        Vertex{-0.5f,  0.5f, -0.5f,
        1.0f, 0.0f, 0.0f, 1.0f},
        // Orange side
        Vertex{-0.5f, -0.5f,  0.5f,
        1.0, 0.6f, 0.0f, 1.0f},
        Vertex{0.5f, -0.5f,  0.5f,
        1.0, 0.6f, 0.0f, 1.0f},
        Vertex{0.5f,  0.5f,  0.5f,
        1.0, 0.6f, 0.0f, 1.0f},
        Vertex{-0.5f,  0.5f,  0.5f,
        1.0, 0.6f, 0.0f, 1.0f},
        // Green side
        Vertex{-0.5f,  0.5f,  0.5f,
        0.0, 1.0f, 0.0f, 1.0f},
        Vertex{-0.5f,  0.5f, -0.5f,
        0.0, 1.0f, 0.0f, 1.0f},
        Vertex{-0.5f, -0.5f, -0.5f,
        0.0, 1.0f, 0.0f, 1.0f},
        Vertex{-0.5f, -0.5f,  0.5f,
        0.0, 1.0f, 0.0f, 1.0f},
        // Blue side
        Vertex{0.5f,  0.5f,  0.5f,
        0.0f, 0.0f, 1.0f, 1.0f},
        Vertex{0.5f,  0.5f, -0.5f,
        0.0f, 0.0f, 1.0f, 1.0f},
        Vertex{0.5f, -0.5f, -0.5f,
        0.0f, 0.0f, 1.0f, 1.0f},
        Vertex{0.5f, -0.5f,  0.5f,
        0.0f, 0.0f, 1.0f, 1.0f},
        // Yellow side
        Vertex{-0.5f, -0.5f, -0.5f,
        1.0f, 1.0f, 0.0f, 1.0f},
        Vertex{0.5f, -0.5f, -0.5f,
        1.0f, 1.0f, 0.0f, 1.0f},
        Vertex{0.5f, -0.5f,  0.5f,
        1.0f, 1.0f, 0.0f, 1.0f},
        Vertex{-0.5f, -0.5f,  0.5f,
        1.0f, 1.0f, 0.0f, 1.0f},
        // White side
        Vertex{-0.5f,  0.5f, -0.5f,
        1.0f, 1.0f, 1.0f, 1.0f},
        Vertex{0.5f,  0.5f, -0.5f,
        1.0f, 1.0f, 1.0f, 1.0f},
        Vertex{0.5f,  0.5f,  0.5f,
        1.0f, 1.0f, 1.0f, 1.0f},
        Vertex{-0.5f,  0.5f,  0.5f,
        1.0f, 1.0f, 1.0f, 1.0f}
    };
    uint32 numVertices = std::size(vertices);

    uint32 indices[] = {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        8, 9, 10,
        10, 11, 8,
        12, 13, 14,
        14, 15, 12,
        16, 17, 18,
        18, 19, 16,
        20, 21, 22,
        22, 23, 20
    };
    uint32 numIndices = std::size(indices);

    IndexBuffer index_buffer(indices, numIndices, sizeof(indices[0]));
    index_buffer.bind();

    VertexBuffer vertexBuffer(vertices, numVertices);
    vertexBuffer.bind();

    Shader shader("../shaders/basic.vert", "../shaders/basic.frag");
    shader.bind();

    uint64 perfCounterFrequency = SDL_GetPerformanceFrequency();
    uint64 lastCounter = SDL_GetPerformanceCounter();
    float32 delta = 0.0f;

    glEnable(GL_DEPTH_TEST);

    float time = 0.0f;
    bool close = false;
    while (!close) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                close = true;
            }
        }
        time += delta;

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model = glm::rotate(model, time * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width) /static_cast<float>(height), 0.1f, 100.0f);

        int modelLocation = glGetUniformLocation(1, "model");
        int viewLocation = glGetUniformLocation(1, "view");
        int projectionLocation = glGetUniformLocation(1, "projection");

        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        vertexBuffer.bind();
        index_buffer.bind();
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
        index_buffer.unbind();
        vertexBuffer.unbind();

        SDL_GL_SwapWindow(window);

        uint64 endCounter = SDL_GetPerformanceCounter();
        uint64 counterElapsed = endCounter - lastCounter;
        delta = (static_cast<float>(counterElapsed)) / static_cast<float>(perfCounterFrequency);
        uint32 FPS = static_cast<uint32>(static_cast<float32>(perfCounterFrequency) / static_cast<float32>(counterElapsed));
        std::cout << FPS << std::endl;
        lastCounter = endCounter;
    }

    return 0;
}
