#include "renderer.h"

Renderer::Renderer()
{
    //-----------------------------------------------------
    // Glew setup
    //-----------------------------------------------------
    glewExperimental = GL_TRUE;
    glewInit();

    //-----------------------------------------------------
    // Create programs
    //-----------------------------------------------------
    GLint status;

    // Create and compile the vertex shader ------------------------------------------
    const char *vertexSource = read_shader_file("shaders/triangles.vert").c_str();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE){

        char buffer[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
        std::cout << buffer << std::endl;

        throw std::runtime_error("Vertex shader compilation failed!");
    }
    //--------------------------------------------------------------------------------

    // Create and compile the fragment shader ----------------------------------------
    const char *fragmentSource = read_shader_file("shaders/triangles.frag").c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE){

        char buffer[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
        std::cout << buffer << std::endl;

        throw std::runtime_error("Fragment shader compilation failed!");
    }
    //--------------------------------------------------------------------------------

    // Link the vertex and fragment shader into a shader program----------------------
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    //--------------------------------------------------------------------------------

    //TODO keep track of all the constructs in the vectors and also in a Map for the programs

}

Renderer::~Renderer(){

    //TODO dispose of all OpenGL constructs

}

void Renderer::clear(){
    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
