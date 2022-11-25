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
    for_each(map_objects.begin(), map_objects.end(),
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
            if (lvlmap[i][j] == '@')
            {
                float x = blockSizeX / 2 + blockSizeX * j;
                float y = sizeY - ( blockSizeY / 2 + blockSizeY * i );

                Wall* wallBlock = new Wall(T(x, y), blockSizeX, blockSizeY, 0.2, 0.0, 0.5);
                map_objects.push_back(wallBlock);
            }
            if ( i+1 < 34 && j + 1 < 65)
            {
                if (lvlmap[i][j] == '.' && lvlmap[i + 1][j] == '.' && 
                    lvlmap[i][j + 1] == '.' && lvlmap[i + 1][j + 1] == '.')
                {
                    float x = blockSizeX + blockSizeX * j;
                    float y = sizeY - (blockSizeY + blockSizeY * i);

                    Coin* coin = new Coin(T(x, y), blockSizeX / 4, (j+i) % 2);
                    map_objects.push_back(coin);
                    ++numCoins;
                }
            }
        }
    }

    std::cout << "Map was successfully initialized. Number of elements is " << map_objects.size() <<
                 ". Number of coins is " << numCoins << std::endl;
}

void Map::print() const
{
    for_each(map_objects.cbegin(), map_objects.cend(),
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
    for_each(map_objects.begin(), map_objects.end(),
        [](DrawingObject* obj) {
            obj->animate();
        }
    );
}
