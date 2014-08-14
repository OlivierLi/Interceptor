#include <iostream>
#include <fstream>
#include <sstream>

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
