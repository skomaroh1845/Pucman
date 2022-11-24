#include "Map.h"
#include "../Primitives/Primitives.h"

#include <fstream>
#include <iostream>
#include <algorithm>



Map::Map(int sizeX, int sizeY) : loaded(false), sizeX(sizeX), sizeY(sizeY)
{
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
    for (int i = 0; i < 36; i++)
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
}

void Map::print() const
{
    for_each(map_objects.begin(), map_objects.end(),
        [](const DrawingObject& obj) {
            obj.print();
        }
    );
}

bool Map::is_loaded() const
{
    return loaded;
}
