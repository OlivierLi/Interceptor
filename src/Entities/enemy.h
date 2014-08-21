#ifndef ENEMY_H
#define ENEMY_H

#include "gameEntity.h"

class Enemy : public GameEntity
{
public:
    Enemy(int x, int y) : GameEntity(x,y) {}
    ~Enemy();
    void update(const World &world);
};

#include "../World/world.h"

#endif // ENEMY_H
