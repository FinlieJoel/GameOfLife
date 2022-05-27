#include "../include/Tile.h"

void Tile::SetAlive()
{
    alive = true;
    Tile::SetSymbol();
}
void Tile::SetDeath()
{
    alive = false;
    Tile::SetSymbol();
}

void Tile::SetSymbol()
{
    if (alive == true)
    {
        symbol = '#';
    }
    else
    {
        symbol = '.';
    }
}
void Tile::SetNeighbours(int &o)
{
    Neighbours = o;
}