#include "gameEntity.h"

GameEntity::GameEntity(int x,int y):pos_x(x),pos_y(y)
{
}

void GameEntity::update(){
    //Input component update
    //physics component update
    pos_x+=2;
}
