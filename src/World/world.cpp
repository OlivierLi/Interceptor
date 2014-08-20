#include "world.h"
#include "../Entities/enemy.h"

World::World()
{
    //Add initial entities here for now, soon they will come from a spawner or clones
    enemies.push_back(Enemy(0,500));
}

//Update all world entities
void World::update(){
    for(auto &entity:enemies){
        entity.update();
    }
}
