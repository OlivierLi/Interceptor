#pragma GCC diagnostic ignored "-Wswitch"

#define GLEW_STATIC
#define MICRO_SECONDS_PER_FRAME 16667

#include <SFML/Window.hpp>
#include <chrono>
#include <unistd.h>
#include <memory>
#include <vector>
#include <iostream>

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

World world(&frame_events);

void setup_display(){
    sf::ContextSettings settings;

    settings.antialiasingLevel = 4;
    settings.majorVersion = 4;
    settings.minorVersion = 3;

    window = std::unique_ptr<sf::Window>(new sf::Window(sf::VideoMode(SCREEN_RESOLUTION_X, SCREEN_RESOLUTION_Y), "OpenGL", sf::Style::Close,settings));
    window->setMouseCursorVisible(false);

    renderer = std::unique_ptr<Renderer::Renderer>(new Renderer::Renderer());
}

void process_input(){

    sf::Event window_event;

    frame_events.clear();

    //This depletes the SFML event queue
    while (window->pollEvent(window_event)) {
        switch (window_event.type) {
            case sf::Event::Closed:
                running = false;
                break;
            case sf::Event::KeyPressed:
                frame_events.push_back(window_event);
                break;
            case sf::Event::MouseMoved:
                frame_events.push_back(window_event);
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

    renderer->display_enemies(world.enemies);
    renderer->display_player(world.player);

    window->display();
}

int main() {

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
        else{
            std::cout << "Processing took: " << microseconds-MICRO_SECONDS_PER_FRAME << " microseconds too long." << std::endl;
        }
    }

    return 0;
}
