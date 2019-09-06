#include "renderer.h"

Renderer::Renderer() {
  //-----------------------------------------------------
  // Glew setup
  //-----------------------------------------------------
  glewExperimental = GL_TRUE;
  glewInit();

  // Create programs and daos
  create_program_and_dao_player();
  create_program_and_dao_enemies();

  // Global settings to set only once
  glEnable(GL_PROGRAM_POINT_SIZE);
}

GLuint Renderer::compile_shader(std::string path, GLuint shader_type) {
  std::string shader_source = read_shader_file(path);
  int shader_source_length = shader_source.length();
  const char* shader_source_cstr = shader_source.c_str();

  GLuint shader = glCreateShader(shader_type);
  glShaderSource(shader, 1, &shader_source_cstr, &shader_source_length);
  glCompileShader(shader);

  GLint status;

  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    char buffer[512];
    glGetShaderInfoLog(shader, 512, NULL, buffer);
    std::cout << buffer << std::endl;

    throw std::runtime_error("Shader compilation failed!");
  }

  return shader;
}

void Renderer::create_program_and_dao_player() {
  // Create and compile the shaders------
  // ------------------------------------------
  GLuint vertexShader =
      compile_shader("../shaders/enemies_vert.glsl", GL_VERTEX_SHADER);
  GLuint fragmentShader =
      compile_shader("../shaders/enemies_frag.glsl", GL_FRAGMENT_SHADER);
  //--------------------------------------------------------------------------------

  // Link the vertex and fragment shader into a shader
  // program----------------------
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  programs.push_back(shaderProgram);
  programs_map.insert(std::pair<std::string, GLuint>("player", shaderProgram));
  //--------------------------------------------------------------------------------

  // Setup
  // uniforms------------------------------------------------------------------

  glUseProgram(shaderProgram);

  GLint uni_screen_resolution =
      glGetUniformLocation(shaderProgram, "screen_resolution");
  glUniform2f(uni_screen_resolution, SCREEN_RESOLUTION_X, SCREEN_RESOLUTION_Y);

  //--------------------------------------------------------------------------------

  // Create dao and map buffer and
  // attrib--------------------------------------------

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Create a Vertex Buffer Object and copy the vertex data to it
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  // Specify the layout of the vertex data
  GLint posAttrib = glGetAttribLocation(programs_map["player"], "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

  vaos_map.insert(std::pair<std::string, GLuint>("player", vao));

  //--------------------------------------------------------------------------------

  // Once shaders are linked in a program they can be be disposed of
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);

  // Unmap program and dao
  glUseProgram(0);
  glBindVertexArray(0);
  glEnableVertexAttribArray(0);
}

void Renderer::create_program_and_dao_enemies() {
  // Create and compile the shaders------
  // ------------------------------------------
  GLuint vertexShader =
      compile_shader("../shaders/enemies_vert.glsl", GL_VERTEX_SHADER);
  GLuint fragmentShader =
      compile_shader("../shaders/enemies_frag.glsl", GL_FRAGMENT_SHADER);
  GLuint geometryShader =
      compile_shader("../shaders/enemies_geo.glsl", GL_GEOMETRY_SHADER);
  //--------------------------------------------------------------------------------

  // Link the vertex and fragment shader into a shader
  // program----------------------
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, geometryShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  programs.push_back(shaderProgram);
  programs_map.insert(std::pair<std::string, GLuint>("enemies", shaderProgram));
  //--------------------------------------------------------------------------------

  // Setup
  // uniforms------------------------------------------------------------------

  glUseProgram(shaderProgram);

  GLint uni_screen_resolution =
      glGetUniformLocation(shaderProgram, "screen_resolution");
  glUniform2f(uni_screen_resolution, SCREEN_RESOLUTION_X, SCREEN_RESOLUTION_Y);

  //--------------------------------------------------------------------------------

  // Create dao and map buffer and
  // attrib--------------------------------------------

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  vaos_map.insert(std::pair<std::string, GLuint>("enemies", vao));

  // Create a Vertex Buffer Object and copy the vertex data to it
  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  //--------------------------------------------------------------------------------

  // Once shaders are linked in a program they can be be disposed of
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);
  glDeleteShader(geometryShader);

  // Unmap program and dao
  glUseProgram(0);
  glBindVertexArray(0);
  glEnableVertexAttribArray(0);
}

void Renderer::display_player(Player player) {
  // Get all the positions of the enemies and put them in the buffer
  std::vector<GLfloat> vertices = {(GLfloat)player.pos_x,
                                   (GLfloat)player.pos_y};

  glUseProgram(programs_map["player"]);
  glBindVertexArray(vaos_map["player"]);

  // Specify the layout of the vertex data
  GLint posAttrib = glGetAttribLocation(programs_map["player"], "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(),
               vertices.data(), GL_DYNAMIC_DRAW);

  // Draw a point to represent the player
  glDrawArrays(GL_POINTS, 0, vertices.size() / 2);

  GLuint err = glGetError();
  if (err != GL_NO_ERROR) {
    std::cout << glewGetErrorString(err) << std::endl;
    throw std::runtime_error("Drawing failed!");
  }
}

void Renderer::display_enemies(const std::vector<Enemy>& enemies) {
  // Get all the positions of the enemies and put them in the buffer
  std::vector<GLfloat> vertices;
  for (const auto& enemy : enemies) {
    vertices.push_back(enemy.pos_x);
    vertices.push_back(enemy.pos_y);
  }

  glUseProgram(programs_map["enemies"]);
  glBindVertexArray(vaos_map["enemies"]);

  // Specify the layout of the vertex data
  GLint posAttrib = glGetAttribLocation(programs_map["enemies"], "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(),
               vertices.data(), GL_DYNAMIC_DRAW);

  // Draw a triangle from the 3 vertices
  glDrawArrays(GL_POINTS, 0, vertices.size() / 2);

  GLuint err = glGetError();
  if (err != GL_NO_ERROR) {
    std::cout << glewGetErrorString(err) << std::endl;
    throw std::runtime_error("Drawing failed!");
  }
}

Renderer::~Renderer() {
  for (auto program : programs) {
    glDeleteProgram(program);
  }

  for (auto& buffer : buffers) {
    glDeleteBuffers(1, &buffer);
  }

  for (auto& vertex_array : vertex_arrays) {
    glDeleteVertexArrays(1, &vertex_array);
  }
}

void Renderer::clear() {
  // Clear the screen to black
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
