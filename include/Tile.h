

class Tile
{

public:
    char symbol;
    bool alive;
    int Neighbours;
    int i;
    void SetAlive();
    void SetDeath();
    void SetSymbol();
    void SetNeighbours(int &);

    Tile(int j) : symbol('.'), alive(false), Neighbours(0), i(j){};
};