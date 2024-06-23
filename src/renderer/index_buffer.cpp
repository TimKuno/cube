#include "index_buffer.h"

IndexBuffer::IndexBuffer(void *data, uint32 numIndices, uint8 elementSize) {
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * elementSize, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &bufferId);
}

void IndexBuffer::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
}

void IndexBuffer::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
