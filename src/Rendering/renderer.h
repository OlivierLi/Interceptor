#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <stdexcept>

#include "../util.hpp"
#include <vector>
#include <map>
#include <array>

#define SCREEN_RESOLUTION_X 1280
#define SCREEN_RESOLUTION_Y 720

class Renderer
{
public:
    Renderer();
    ~Renderer();
    void clear();
    void display_enemies();
private:

    //Used to keep track of all ressources to dealocate
    std::vector<GLuint> shaders;
    std::vector<GLuint> programs;
    std::vector<GLuint> buffers;
    std::vector<GLuint> vertex_arrays;

    //Used to select programs
    std::map<std::string,GLuint> programs_map;

    //Used to select daos
    std::map<std::string,GLuint> vaos_map;

    void create_program_and_dao_enemies();
    void test_shader_compilation(GLuint shader);

    std::vector<GLfloat> vertices { {    800 , 600,
                                         900 , 700,
                                         1280 , 600,
                                         0    , 0,
                                         100  , 100,
                                         200  , 0
                                  } };

};

#endif // RENDERER_H
