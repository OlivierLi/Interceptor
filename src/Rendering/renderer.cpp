#include "renderer.h"

Renderer::Renderer()
{
}

void Renderer::clear(){
    // Clear the screen to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
