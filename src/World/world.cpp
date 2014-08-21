#include "world.h"
#include "../Entities/enemy.h"

World::World(std::vector<sf::Event> *event_queue):player(0,0), frame_events(event_queue)
{
    //Add initial entities here for now, soon they will come from a spawner or clones
    enemies.push_back(Enemy(0,500));
}

//Update all world entities
void World::update(){

    for(auto &entity:enemies){
        entity.update(*this);
    }

    player.update(*this);
}
