#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "../Entities/enemy.h"

class World
{
public:
    World();
    void update();
    std::vector<Enemy> enemies;
private:
};

#endif // WORLD_H
