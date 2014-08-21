#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "player.h"
#include "../common.h"

void Player::update(const World &world){

    //Find the first mouse move event and move the player to that location
    for(sf::Event &event:*world.frame_events){
        if(event.type == sf::Event::MouseMoved){
            pos_x = event.mouseMove.x;
            pos_y = SCREEN_RESOLUTION_Y - event.mouseMove.y;
        }
    }
}

Player::~Player(){
    ;
}
