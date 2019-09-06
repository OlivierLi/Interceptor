#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "enemy.h"

void Enemy::update(const World& world) {
  // Input component update
  // physics component update
  pos_x += 1;

  // Enemy has gone over the edge, it's dead
  if (pos_x >= SCREEN_RESOLUTION_X) {
    dead = true;
  }

  // If the enemy collided with the player, it's dead
  int distance = world.player.get_distance(pos_x, pos_y);
  if (distance < 10) {
    dead = true;
  }
}

bool Enemy::is_dead() const {
  return dead;
}

Enemy::~Enemy() = default; 
