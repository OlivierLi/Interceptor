#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "../common.h"
#include "gameEntity.h"

class Player : public GameEntity {
 public:
  Player(int x, int y) : GameEntity(x, y) {}
  ~Player();
  void update(const World& world) override;
  int get_distance(int x, int y) const;

 private:
  std::vector<std::pair<int, int>> last_known_positions;
};

#include "../World/world.h"

#endif  // PLAYER_H
