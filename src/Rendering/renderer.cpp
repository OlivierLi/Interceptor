#include "renderer.h"

Renderer::Renderer()
{
    //-----------------------------------------------------
    // Glew setup
    //-----------------------------------------------------
    glewExperimental = GL_TRUE;
    glewInit();

    //Create programs
    create_program("shaders/triangles.vert","shaders/triangles.frag","triangles");
}

void Renderer::create_program(std::string vertex_path, std::string fragment_path ,std::string program_name){

    // Create and compile the vertex shader ------------------------------------------
    const char *vertexSource = read_shader_file(vertex_path).c_str();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    test_shader_compilation(vertexShader);

    shaders.push_back(vertexShader);
    //--------------------------------------------------------------------------------

    // Create and compile the fragment shader ----------------------------------------
    const char *fragmentSource = read_shader_file(fragment_path).c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    test_shader_compilation(fragmentShader);

    shaders.push_back(fragmentShader);
    //--------------------------------------------------------------------------------

    // Link the vertex and fragment shader into a shader program----------------------
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);

    programs.push_back(shaderProgram);
    programs_map.insert(std::pair<std::string,GLuint>(program_name,shaderProgram));
    //--------------------------------------------------------------------------------

    //Set the format of buffers for now. Later we will use different formats
}

void Renderer::test_shader_compilation(GLuint shader){
    GLint status;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE){

        char buffer[512];
        glGetShaderInfoLog(shader, 512, NULL, buffer);
        std::cout << buffer << std::endl;

        throw std::runtime_error("Fragment shader compilation failed!");
    }
}

Renderer::~Renderer(){

    for(auto program:programs){
        glDeleteProgram(program);
    }

    for(auto shader:shaders){
        glDeleteShader(shader);
    }

    for(auto &buffer:buffers){
        glDeleteBuffers(1, &buffer);
    }

    for(auto &vertex_array:vertex_arrays){
        glDeleteVertexArrays(1,&vertex_array);
    }

}

void Renderer::clear(){
    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
