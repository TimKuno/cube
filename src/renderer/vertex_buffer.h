#pragma once
#include <GL/glew.h>

#include "../utils/data_types.h"

class VertexBuffer {
private:
    GLuint bufferId;
    GLuint vao;

public:
    VertexBuffer(void* data, uint32 numVertices);

    virtual ~VertexBuffer();

    void bind();
    void unbind();
};
