#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "../Entities/gameEntity.h"

class World
{
public:
    World();
    void update();
    std::vector<GameEntity> entities;
private:
};

#endif // WORLD_H
