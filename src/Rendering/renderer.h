#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <stdexcept>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <array>

#include "../Entities/enemy.h"
#include "../Entities/player.h"

#define SCREEN_RESOLUTION_X 1280
#define SCREEN_RESOLUTION_Y 720

inline std::string read_shader_file(std::string shader_file_name){

    std::ifstream stream(shader_file_name);

    if(!stream)
    {
        std::cout<< shader_file_name << " file not found." << std::endl;
        exit(1);
    }

    std::stringstream buffer;
    buffer << stream.rdbuf();

    std::string program_source = buffer.str();

    if(program_source.length()==0)
    {
        std::cout<< shader_file_name << " is empty." << std::endl;
        exit(1);
    }

    return program_source;
}

class Renderer
{
public:
    Renderer();
    ~Renderer();
    void clear();
    void display_enemies(const std::vector<Enemy> &enemies);
    void display_player(Player player);
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
