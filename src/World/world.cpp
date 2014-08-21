#include "world.h"
#include "../Entities/enemy.h"
#include "../common.h"

World::World(std::vector<sf::Event> *event_queue):player(0,0), frame_events(event_queue) {
    //First wave, later wave will start periodically
    spawn_enemies();
}

void World::spawn_enemies() {

    //int x_spacing = 0;
    int y_spacing   = 20;
    int x_padding = 0;
    int y_padding = SCREEN_RESOLUTION_Y - (wave*enemies_per_wave*y_spacing);

    for(int i=0; i<wave*enemies_per_wave; ++i) {
        enemies.push_back(Enemy(x_padding,y_padding+y_spacing*i));
    }
}

//Update all world entities
void World::update() {

    //Update all enemies
    for(auto &entity:enemies) {
        entity.update(*this);
    }

    //Remove dead enemies from the list
    for (std::vector<Enemy>::iterator it=enemies.begin(); it!=enemies.end();) {
        if(it->is_dead()) {
            it = enemies.erase(it);
        }
        else{
            ++it;
        }
    }

    //No more enemies, time to create another wave
    if(enemies.empty()) {
        ++wave;
        spawn_enemies();
    }

    player.update(*this);
}
