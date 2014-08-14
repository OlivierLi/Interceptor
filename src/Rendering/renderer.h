#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <stdexcept>

#include "../util.hpp"
#include <vector>

class Renderer
{
public:
    Renderer();
    ~Renderer();
    void clear();
private:
    std::vector<GLuint> shaders;
    std::vector<GLuint> programs;
    std::vector<GLuint> buffers;
    std::vector<GLuint> vertex_arrays;
};

#endif // RENDERER_H
