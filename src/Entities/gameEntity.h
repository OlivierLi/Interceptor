#pragma GCC diagnostic ignored "-Wunused-private-field"

#ifndef GAMEENTITY_H
#define GAMEENTITY_H

class GameEntity
{
public:
    int pos_x,pos_y;
    GameEntity(int x,int y);

    virtual void update()=0;
private:

};

#endif // GAMEENTITY_H
