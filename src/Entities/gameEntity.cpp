#include "gameEntity.h"

GameEntity::GameEntity()
{
    pos_x = 0;
    pos_y = 500;
}

void GameEntity::update(){
    //Input component update
    //physics component update
    pos_x+=2;
}
