#ifndef PLAYER_H
#define PLAYER_H

#include "gameEntity.h"

class Player : public GameEntity
{
public:
    Player(int x, int y):GameEntity(x,y){}
    ~Player();
    void update(const World &world);
};

#include "../World/world.h"

#endif // PLAYER_H
