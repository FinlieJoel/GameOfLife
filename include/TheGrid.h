#include <iostream>
#include "../include/Tile.h"
#include <vector>
#include <memory>

class TheGrid
{
    int gridSize;
    int tempNeighs;
    void makeAlive();
    void Rule1();
    void Rule2();
    void Rule3();
    void Rule4();
    void GameLoop();
    void pause();
    void AddTiles();
    void ManualControl();
    void TileInput();
    void InputLine();

public:
    TheGrid();
    void display();
    void itsAlive();
    std::vector<std::shared_ptr<Tile>> grid;
    std::vector<int> activeTiles;
    void rules();
};
