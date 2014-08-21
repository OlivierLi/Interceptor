#pragma GCC diagnostic ignored "-Wunused-private-field"

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "../Entities/enemy.h"
#include "../Entities/player.h"

#include <SFML/Window.hpp>

class World
{
public:
    World(std::vector<sf::Event> *event_queue);
    void update();
    std::vector<Enemy> enemies;
    Player player;

    std::vector<sf::Event> *frame_events;

private:


};

#endif // WORLD_H
