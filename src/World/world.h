#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "../Entities/gameEntity.h"

class World
{
public:
    World();
    void update();
private:
    std::vector<GameEntity> entities;
};

#endif // WORLD_H
