#pragma once

#include <GL/glew.h>
#include <string>

class Shader {
private:
    GLuint shaderId;

    std::string parse(const char* filename);
    GLuint compile(std::string shaderSource, GLenum type);
    GLuint createShader(const char* vertexShaderFilename, const char* fragmentShaderFilename);
public:
    Shader(const char* vertexShaderFilename, const char* fragmentShaderFilename);
    virtual  ~Shader();

    void bind();
    void unbind();
};