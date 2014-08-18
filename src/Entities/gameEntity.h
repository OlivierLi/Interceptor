#pragma GCC diagnostic ignored "-Wunused-private-field"

#ifndef GAMEENTITY_H
#define GAMEENTITY_H

class GameEntity
{
public:
    GameEntity();
    void update();
private:
    int pos_x,pos_y;
};

#endif // GAMEENTITY_H
