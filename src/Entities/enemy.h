#ifndef ENEMY_H
#define ENEMY_H

#include <cmath>
#include "../common.h"
#include "gameEntity.h"

class Enemy : public GameEntity {
 public:
  Enemy(int x, int y) : GameEntity(x, y) {}
  virtual ~Enemy();
  void update(const World& world) override;
  bool is_dead() const;

 private:
  bool dead = false;
};

#include "../World/world.h"

#endif  // ENEMY_H
