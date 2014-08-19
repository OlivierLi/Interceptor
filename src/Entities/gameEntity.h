#pragma GCC diagnostic ignored "-Wunused-private-field"

#ifndef GAMEENTITY_H
#define GAMEENTITY_H

class GameEntity
{
public:
    GameEntity(int x,int y);
    void update();
    int pos_x,pos_y;
private:

};

#endif // GAMEENTITY_H
