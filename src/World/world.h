#pragma GCC diagnostic ignored "-Wunused-private-field"

#ifndef WORLD_H
#define WORLD_H

#include <SFML/Window.hpp>
#include <climits>
#include <vector>

#include "../Entities/enemy.h"
#include "../Entities/player.h"
#include "../common.h"

class World {
 public:
  World(std::vector<sf::Event>* event_queue);
  void update();
  std::vector<Enemy> enemies;
  Player player;

  std::vector<sf::Event>* frame_events;

 private:
  void spawn_enemies();
  int wave = 1;
  int enemies_per_wave = 10;
};

#endif  // WORLD_H
