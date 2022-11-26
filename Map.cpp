#include "Map.h"
#include "../Primitives/Primitives.h"
#include "../Primitives/Vector2D.h"
#include "Coin.h"
#include "Wall.h"

#include <fstream>
#include <iostream>
#include <algorithm>


Map::Map(int sizeX, int sizeY) : loaded(false), sizeX(sizeX), sizeY(sizeY), numCoins(0)
{
}

Map::~Map()
{
    for_each(walls.begin(), walls.end(),
        [](DrawingObject* obj) {
            delete obj;
        }
    );
}

void Map::loadMap(const char* path)
{
    ifstream f(path);
    if (!f.is_open())
    {
        cout << "Lvl map file could not be opened." << endl;
        return;
    }
    char a;
    cout << "Lvl file reading..." << endl;
    for (int i = 0; i < 34; i++)
    {
        for (int j = 0; j < 65; j++)
        {
            f.get(a);
            cout << a;  // for debug 
            
            if (a != '\n' && a != '\0') 
                lvlmap[i][j] = a;
        }
    }
    f.close();
    loaded = true;
    cout << "Lvl map is loaded." << endl;
}

void Map::mapInit()
{
    // Here is you need to interpret symbols as objects like 'walls' or 'coins' 
    float blockSizeX = float(sizeX) / 64.0;
    float blockSizeY = float(sizeY) / 34.0;

    for (int i = 0; i < 34; ++i)
    {
        for (int j = 0; j < 65; ++j)
        {
            if (lvlmap[i][j] == '@')  // Walls
            {
                float x = blockSizeX / 2 + blockSizeX * j;
                float y = sizeY - ( blockSizeY / 2 + blockSizeY * i );

                Wall* wallBlock = new Wall(T(x, y), blockSizeX, blockSizeY, 0.2, 0.0, 0.5);
                walls.push_back(wallBlock);
            }
            if ( i+1 < 34 && j + 1 < 65)  // Coins
            {
                if (lvlmap[i][j] == '.' && lvlmap[i + 1][j] == '.' && 
                    lvlmap[i][j + 1] == '.' && lvlmap[i + 1][j + 1] == '.')
                {
                    float x = blockSizeX + blockSizeX * j;
                    float y = sizeY - (blockSizeY + blockSizeY * i);

                    Coin* coin = new Coin(T(x, y), blockSizeX / 4, (j+i) % 2);
                    coins.push_back(coin);
                    ++numCoins;

                    if (rand() % 100 == 1) {           // Get random spawn coordinates
                        creatureSpawn.push_back(T(x, y)); 
                    }
                }
            }
        }
    }

    std::cout << "Map was successfully initialized. Number of walls is " << walls.size() <<
                 ". Number of coins is " << numCoins << std::endl;
    std::cout << creatureSpawn.size() << std::endl;
    
}

void Map::print() const
{
    for_each(walls.cbegin(), walls.cend(),
        [](const Wall* obj) {
            obj->print();
        }
    );
    for_each(coins.cbegin(), coins.cend(),
        [](const DrawingObject* obj) {
            obj->print();
        }
    );
}

bool Map::is_loaded() const
{
    return loaded;
}

void Map::animate()
{
    for_each(coins.begin(), coins.end(),
        [](DrawingObject* obj) {
            obj->animate();
        }
    );
}

T Map::getSpawn(int spawnNum)
{
    spawnNum = spawnNum % creatureSpawn.size();
    T playerSpawn = creatureSpawn[spawnNum];
    creatureSpawn.erase(creatureSpawn.begin() + spawnNum);
    return playerSpawn;
}

float Map::getSize() const
{
    return float(sizeX) / 64.0 * 0.8;
}

vector<Wall*>& Map::getWallsGroup()
{
    return walls;
}

vector<DrawingObject*>& Map::getCoinsGroup()
{
    return coins;
}
