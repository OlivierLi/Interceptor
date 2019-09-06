#ifndef ENEMY_H
#define ENEMY_H

#include "gameEntity.h"
#include "../common.h"
#include <cmath>

class Enemy : public GameEntity
{
public:
    Enemy(int x, int y) : GameEntity(x,y) {}
    virtual ~Enemy();
    void update(const World &world) override;
    bool is_dead();
private:
    bool dead = false;
};

#include "../World/world.h"

#endif // ENEMY_H
