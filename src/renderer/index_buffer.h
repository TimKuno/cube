#pragma once
#include <GL/glew.h>

#include "../utils/data_types.h"

class IndexBuffer {
private:
    GLuint bufferId;

public:
    IndexBuffer(void* data, uint32 numIndices, uint8 elementSize);
    virtual ~IndexBuffer();

    void bind();
    void unbind();
};