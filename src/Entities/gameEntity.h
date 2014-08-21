#ifndef GAMEENTITY_H
#define GAMEENTITY_H

class World;

class GameEntity
{
public:
    int pos_x,pos_y;
    GameEntity(int x,int y):pos_x(x),pos_y(y) {}
    virtual void update(const World &world)=0;
private:
};

#endif // GAMEENTITY_H
