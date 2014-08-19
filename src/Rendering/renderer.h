#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <stdexcept>

#include "../util.hpp"
#include <vector>
#include <map>
#include <array>

#include "../Entities/gameEntity.h"

#define SCREEN_RESOLUTION_X 1280
#define SCREEN_RESOLUTION_Y 720

class Renderer
{
public:
    Renderer();
    ~Renderer();
    void clear();
    void display_enemies(const std::vector<GameEntity> &enemies);
    void display_player(GameEntity player);
private:

    //Used to keep track of all ressources to dealocate
    std::vector<GLuint> programs;
    std::vector<GLuint> buffers;
    std::vector<GLuint> vertex_arrays;

    //Used to select programs
    std::map<std::string,GLuint> programs_map;

    //Used to select daos
    std::map<std::string,GLuint> vaos_map;

    void create_program_and_dao_enemies();
    void create_program_and_dao_player();
    GLuint compile_shader(std::string path,GLuint shader_type);
};

#endif // RENDERER_H
