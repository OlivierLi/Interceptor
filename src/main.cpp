#pragma GCC diagnostic ignored "-Wswitch"

#define GLEW_STATIC
#define MICRO_SECONDS_PER_FRAME 16667

#include <SFML/Window.hpp>
#include <chrono>
#include <unistd.h>
#include <memory>
#include <vector>
#include <iostream>
#include <stdlib.h>

#include "Rendering/renderer.h"
#include "World/world.h"

//Flow control and timing
std::chrono::steady_clock::time_point start;
std::chrono::steady_clock::time_point end;
bool running = true;

//Rendering and display
std::unique_ptr<sf::Window> window;
std::unique_ptr<Renderer::Renderer> renderer;

//Keeps only the events we want for the current frame
std::vector<sf::Event> frame_events;

World world;

void setup_display(){
    sf::ContextSettings settings;

    settings.antialiasingLevel = 4;
    settings.majorVersion = 4;
    settings.minorVersion = 3;

    window = std::unique_ptr<sf::Window>(new sf::Window(sf::VideoMode(SCREEN_RESOLUTION_X, SCREEN_RESOLUTION_Y), "OpenGL", sf::Style::Close,settings));
    renderer = std::unique_ptr<Renderer::Renderer>(new Renderer::Renderer());
}

void process_input(){

    sf::Event window_event;

    //This depletes the SFML event queue
    while (window->pollEvent(window_event)) {
        switch (window_event.type) {
            case sf::Event::Closed:
                running = false;
                break;
            case sf::Event::KeyPressed:
                frame_events.push_back(window_event);
                break;
                //We do not handle long key presses for now
            case sf::Event::KeyReleased:
                break;
            default:
                break;
        }
    }
}

void update(){
    world.update();
}

void render(){
    renderer->clear();

    //TEST ADD A RANDOMLY POSITIONED POINT
    int random_int_x = rand() % 1280 + 1;
    int random_int_y = rand() % 720 + 1;
    renderer->vertices.push_back(random_int_x);
    renderer->vertices.push_back(random_int_y);
    //TEST END----------------------------

    renderer->display_enemies();
    window->display();
}

int main() {

    /* initialize random seed: */
      srand (time(NULL));

    //-----------------------------------------------------
    // SFML and rendering setup
    //-----------------------------------------------------
    setup_display();

    //-----------------------------------------------------
    // Main game loop
    //-----------------------------------------------------
    while (running) {

        //Get the time at the beginning of the frame
        start = std::chrono::steady_clock::now();

        process_input();
        update();
        render();

        //Calculate how long the frame took to process
        end = std::chrono::steady_clock::now();
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();

        //Sleep if the processing took less than what is necessary to achieve 60 FPS
        if(( MICRO_SECONDS_PER_FRAME - microseconds ) > 0){
            usleep((MICRO_SECONDS_PER_FRAME - microseconds));
        }
    }

    return 0;
}
