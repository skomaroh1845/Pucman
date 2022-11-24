#pragma once

#include <vector>
#include "../Primitives/DrawingObject.h"

using namespace std;

// It is a class of game map
class Map final
{
	char lvlmap[34][65];   // loads from file
	bool loaded;

	int sizeX, sizeY;   

	vector<DrawingObject*> map_objects;

public: 

	Map(int sizeX, int sizeY);

	~Map();

	void loadMap(const char* path);

	void mapInit();

	void print() const;

	bool is_loaded() const;

};

