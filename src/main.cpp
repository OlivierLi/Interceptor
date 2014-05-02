#pragma GCC diagnostic ignored "-Wswitch"

#define GLEW_STATIC
#define MICRO_SECONDS_PER_FRAME 16667

#include <GL/glew.h>
#include <SFML/Window.hpp>
#include <chrono>
#include <unistd.h>

std::chrono::steady_clock::time_point start;
std::chrono::steady_clock::time_point end;

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

        start = std::chrono::steady_clock::now();

        while (window.pollEvent(windowEvent)) {
            switch (windowEvent.type) {
            case sf::Event::Closed:
                running = false;
                break;
            }
        }

        window.display();

        end = std::chrono::steady_clock::now();
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

        //Sleep if the processing took less than what is necessary to achieve 60 FPS
        if(( MICRO_SECONDS_PER_FRAME - microseconds ) > 0){
            usleep((MICRO_SECONDS_PER_FRAME - microseconds));
        }
    }

    return 0;
}
