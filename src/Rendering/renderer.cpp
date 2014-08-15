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
    std::string vertex_shader_source = read_shader_file(vertex_path);
    int vertex_shader_source_length = vertex_shader_source.length();
    const char *vertex_shader_source_cstr = vertex_shader_source.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader_source_cstr, &vertex_shader_source_length);
    glCompileShader(vertexShader);
    test_shader_compilation(vertexShader);

    shaders.push_back(vertexShader);
    //--------------------------------------------------------------------------------

    // Create and compile the fragment shader ----------------------------------------
    std::string fragment_shader_source = read_shader_file(fragment_path);
    int fragment_shader_source_length = fragment_shader_source.length();
    const char *fragment_shader_source_cstr = fragment_shader_source.c_str();

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader_source_cstr, &fragment_shader_source_length);
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
}

void Renderer::display_enemies(){

    glUseProgram(programs_map["triangles"]);

    //TEMPORARY CODE TO VERIFY THAT EVERYTHING STILL WORKS
    //--------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------
    // Create Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);

    std::vector<GLfloat> vertices { {    0.0f,  0.2f,
                                         0.2f, -0.2f,
                                        -0.2f, -0.2f,
                                         0.2f,  0.0f,
                                         0.5f, -0.5f,
                                       - 0.5f, -0.5f} };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*vertices.size(), vertices.data() , GL_STATIC_DRAW);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(programs_map["triangles"], "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // Draw a triangle from the 3 vertices
    glDrawArrays(GL_TRIANGLES, 0, vertices.size()/2 );

    //--------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------
    //--------------------------------------------------------------------------------------------------
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
