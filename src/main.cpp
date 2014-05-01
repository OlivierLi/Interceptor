#pragma GCC diagnostic ignored "-Wswitch"

#define GLEW_STATIC

#include <GL/glew.h>
#include <SFML/Window.hpp>

int main() {

    //-----------------------------------------------------
    // SFML setup
    //-----------------------------------------------------
    sf::Window window(sf::VideoMode(1280, 720), "OpenGL", sf::Style::Close);
    sf::Event windowEvent;

    //-----------------------------------------------------
    // Glew setup
    //-----------------------------------------------------
    glewExperimental = GL_TRUE;
    glewInit();

    //-----------------------------------------------------
    // Main game loop
    //-----------------------------------------------------
    bool running = true;
    while (running) {

        while (window.pollEvent(windowEvent)) {
            switch (windowEvent.type) {
            case sf::Event::Closed:
                running = false;
                break;
            }
        }

        window.display();
    }

    return 0;
}
