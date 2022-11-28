#include "Map.h"
#include "../Primitives/Primitives.h"
#include "../Primitives/Vector2D.h"
#include "Coin.h"
#include "Wall.h"

#include <fstream>
#include <iostream>
#include <algorithm>


Map::Map(int sizeX, int sizeY) : loaded(false), sizeX(sizeX), sizeY(sizeY), numCoins(0), score(0)
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

                    if (rand() % 50 == 1) {           // Get random spawn coordinates
                        creatureSpawn.push_back(T(x, y)); 
                    }
                }
            }
        }
    } 
    numGhosts = creatureSpawn.size() - 1;
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
    return min(float(sizeX) / 64.0, float(sizeY) / 34.0) * 0.8;
}

vector<Wall*>& Map::getWallsGroup()
{
    return walls;
}

vector<DrawingObject*>& Map::getCoinsGroup()
{
    return coins;
}

void Map::updateCreaturesView(const vector<Creature*>& creatures) const
{
    float lookY = 1.75 * walls[0]->getSizeY();
    float lookX = 1.75 * walls[0]->getSizeX();

    for (Creature* Cr : creatures) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j)
                Cr->view[i][j] = 0;
        }
    }

    for (const Wall* wall : walls) 
    {
        for (Creature* Cr : creatures)
        {
            if (abs(wall->getCenter().x - Cr->getCenter().x) > lookX ||
                abs(wall->getCenter().y - Cr->getCenter().y) > lookY)
                continue;

            Cr->updateView(wall);
        }      
    }
}

void Map::updateCoins(const T& playerPos)
{
    int k = -1;

    for (int i = 0; i < coins.size(); ++i) {
        if ( (coins[i]->getCenter() - playerPos).length() < getSize() * 2 / 3)
        {
            ++score;
            cout << score << endl;
            k = i;
            break;
        }
    }

    if (k > -1)
        coins.erase(coins.begin() + k);
}
