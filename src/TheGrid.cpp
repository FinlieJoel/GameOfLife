#include "../include/TheGrid.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <conio.h>
#include <limits>
#include <cstddef>

TheGrid::TheGrid()
{
    std::cout << "How large would you like the grid? \n";
    std::cin >> gridSize;
    // gridSize = 10;
    int k = 0;
    int x, y;
    bool e = true;
    char input;

    std::cout << "Would you like an automatic shape in the middle? (y/n)\n";
    std::cin >> input;
    do
    {
        switch (input)
        {
        case 'n':
            TheGrid::TileInput();
            e = false;
            break;
        case 'N':
            TheGrid::TileInput();
            e = false;
            break;
        case 'y':
            TheGrid::InputLine();
            e = false;
            break;
        case 'Y':
            TheGrid::InputLine();
            e = false;
            break;
        default:
            std::cout << "Try again .. \n";
            break;
        }
    } while (e == true);

    for (int i = 0; i < gridSize * gridSize; i++)
    {
        k++;
        std::shared_ptr<Tile> NewTile = std::make_shared<Tile>(k);
        grid.push_back(NewTile);
    }
    TheGrid::makeAlive();
    TheGrid::GameLoop();
}

void TheGrid::InputLine()
{
    for (int j = -1; j < 2; j++)
    {
        activeTiles.push_back(((gridSize / 2) * gridSize) - ((gridSize / 2)) + (j * gridSize));
    }
}

void TheGrid::TileInput()
{
    char input;
    bool e = true;
    do
    {
        std::cout << "Would you like to make a square alive? (y/n) \n";
        std::cin >> input;
        switch (input)
        {
        case 'y':
            TheGrid::AddTiles();
            break;
        case 'Y':
            TheGrid::AddTiles();
            break;
        case 'n':
            e = false;
            break;
        case 'N':
            e = false;
            break;

        default:
            std::cout << "Invalid input..\n";
            break;
        }

    } while (e == true);
}

void TheGrid::AddTiles()
{
    bool isOkay = true;
    int x, y;
    std::cout << "Which tile coordinates would you like to come alive? ie. x co-ordinate <enter>, y co-ordinate <enter> \n";
    std::cin >> x;
    // if (std::cin >> x)
    // {
    //     std::cout << "Incorrect input .. \n";
    //     std::cin.clear();
    //     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //     isOkay = false;
    // }
    std::cin >> y;
    // if (std::cin.fail())
    // {
    //     std::cout << "Incorrect input .. \n";
    //     isOkay = false;
    // }
    // if (isOkay == true)
    // {
    activeTiles.push_back((y - 1) * gridSize + x);
    // }
}

void TheGrid::GameLoop()
{
    do
    {
        TheGrid::pause();
        std::cout << "press p to pause, m to go manual, r to restart.. \n";
        TheGrid::display();
        TheGrid::itsAlive();
        TheGrid::rules();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } while (true);
}

void TheGrid::pause()
{
    char i = 'f';
    char input;
    if (kbhit())
    {
        i = getch();
        if (i == 'P' || i == 'p')
        {
            std::cout << "You have paused the game.. press any key and enter to keep going\n";
            std::cin >> input;
        }
        else if (i == 'R' || i == 'r')
        {
            std::cout << "You have restarted the game.. press any key and enter to restart\n";
            std::cin >> input;
            TheGrid::makeAlive();
        }
        else if (i == 'M' || i == 'm')
        {
            TheGrid::ManualControl();
        }
    }
    system("cls");
}

void TheGrid::ManualControl()
{
    bool exit = false;
    char turn;
    std::cout << "You have entered manual control\n";
    do
    {
        std::cout << "Another turn: (t). To enter automatic mode: (a)\n";
        std::cin >> turn;
        switch (turn)
        {
        case 't':
            TheGrid::pause();
            TheGrid::display();
            TheGrid::itsAlive();
            TheGrid::rules();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
        case 'T':
            TheGrid::pause();
            TheGrid::display();
            TheGrid::itsAlive();
            TheGrid::rules();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            break;
        case 'a':
            exit = true;
            break;
        case 'A':
            exit = true;
            break;

        default:
            std::cout << "incorrect input\n";
            break;
        }
    } while (exit == false);
}

void TheGrid::rules()
{
    TheGrid::Rule1();
    // TheGrid::Rule2(); // Do not need this rule ..
    TheGrid::Rule3();
    TheGrid::Rule4();
}
void TheGrid::Rule1()
{
    for (std::vector<std::shared_ptr<Tile>>::iterator i = grid.begin(); i != grid.end(); i++)
    {
        if ((*i)->Neighbours < 2)
        {
            (*i)->SetDeath();
        }
    }
    // 1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
};

void TheGrid::Rule2()
{
    for (std::vector<std::shared_ptr<Tile>>::iterator i = grid.begin(); i != grid.end(); i++)
    {
        if ((*i)->Neighbours == 2 || (*i)->Neighbours == 3)
        {
            (*i)->SetAlive();
        }
    }
    // 2. Any live cell with two or three live neighbours lives on to the next generation.
};
void TheGrid::Rule3()
{
    for (std::vector<std::shared_ptr<Tile>>::iterator i = grid.begin(); i != grid.end(); i++)
    {
        if ((*i)->Neighbours > 3)
        {
            (*i)->SetDeath();
        }
    }
    // 3. Any live cell with more than three live neighbours dies, as if by over-population.
};
void TheGrid::Rule4()
{
    for (std::vector<std::shared_ptr<Tile>>::iterator i = grid.begin(); i != grid.end(); i++)
    {
        if ((*i)->Neighbours == 3)
        {
            (*i)->SetAlive();
        }
    }
    // 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
};

void TheGrid::makeAlive()
{
    int j = 0;
    for (std::vector<std::shared_ptr<Tile>>::iterator i = grid.begin(); i != grid.end(); i++)
    {
        (*i)->SetDeath();

        j++;
        for (std::vector<int>::iterator k = activeTiles.begin(); k != activeTiles.end(); k++)
        {
            if (j == *k)
            {
                (*i)->SetAlive();
            }
        }
    }
}

void TheGrid::itsAlive()
{
    for (std::vector<std::shared_ptr<Tile>>::iterator i = grid.begin(); i != grid.end(); i++)
    {
        // This function checks to see how many alive neighbours each tile has
        tempNeighs = 0;
        auto j = i;
        {
            std::advance(i, -gridSize);

            for (int l = 0; l < 3; l++)
            {
                if ((i - 1) >= grid.begin() && (i - 1) < grid.end() && (*(i - 1))->alive == true)
                {
                    if ((((*(i - 1))->i) % gridSize) != 0)
                    {
                        tempNeighs++;
                    }
                }
                if (i >= grid.begin() && i <= grid.end() && (*i)->alive == true)
                {
                    tempNeighs++;
                }
                if ((i + 1) >= grid.begin() && (i + 1) < grid.end() && (*(i + 1))->alive == true)
                {
                    if (((*(i + 1))->i % gridSize) != 1)
                    {
                        tempNeighs++;
                    }
                }
                if ((i + gridSize) < grid.end())
                {
                    std::advance(i, gridSize);
                }
                else
                {
                    l++;
                }
            }
        }

        i = j;

        if ((*i)->alive == true)
        {
            tempNeighs--;
        }
        (*i)->SetNeighbours(tempNeighs);
    }
}

void TheGrid::display()
{
    std::cout << "You have accessed the grid"
              << "\n";
    int j = 0;
    for (std::vector<std::shared_ptr<Tile>>::iterator i = grid.begin(); i != grid.end(); i++)
    {
        std::cout << (*i)->symbol << " "; // for printing the vector
        j++;
        if (j % gridSize == 0)
        {
            std::cout << "\n";
        }
    }
};