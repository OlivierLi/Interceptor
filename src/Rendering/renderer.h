#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <stdexcept>

#include "../util.hpp"
#include <vector>
#include <map>

class Renderer
{
public:
    Renderer();
    ~Renderer();
    void clear();
    void display_triangles();
private:

    //Used to keep track of all ressources to dealocate
    std::vector<GLuint> shaders;
    std::vector<GLuint> programs;
    std::vector<GLuint> buffers;
    std::vector<GLuint> vertex_arrays;

    //Use to select programs
    std::map<std::string,GLuint> programs_map;

    void create_program(std::string vertex_path, std::string fragment_path ,std::string program_name);
    void test_shader_compilation(GLuint shader);

};

#endif // RENDERER_H
