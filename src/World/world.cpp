#include "world.h"
#include "../Entities/gameEntity.h"

World::World()
{
    //Add initial entities here for now, soon they will come from a spawner or clones
    entities.push_back(GameEntity(0,500));
}

//Update all world entities
void World::update(){
    for(auto &entity:entities){
        entity.update();
    }
}
