#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "enemy.h"


void Enemy::update(const World &world){
    //Input component update
    //physics component update
    pos_x+=2;

    //Enemy has gone over the edge, it's dead
    if(pos_x >= SCREEN_RESOLUTION_X ){
        dead = true;
    }

    //If the enemy collided with the player, it's dead
    int distance = sqrt(pow((pos_x-world.player.pos_x),2)+pow((pos_y-world.player.pos_y),2));
    if(distance < 10){
        dead = true;
    }

}

bool Enemy::is_dead(){
    return dead;
}

Enemy::~Enemy(){
    ;
}
