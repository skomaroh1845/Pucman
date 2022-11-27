#pragma once

#include <vector>
#include "../Primitives/DrawingObject.h"
#include "Wall.h"
#include "Creature.h"

using namespace std;

// It is a class of game map
class Map final
{
	char lvlmap[34][65];   // loads from file
	bool loaded;

	int sizeX, sizeY;        // technical info
	vector<T> creatureSpawn;

	vector<Wall*> walls;  // walls and coins
	vector<DrawingObject*> coins;
	
public:
	int numCoins;

	Map(int sizeX, int sizeY);

	~Map();

	void loadMap(const char* path);

	void mapInit();

	void print() const;

	bool is_loaded() const;

	void animate();

	T getSpawn(int spawnNum);

	float getSize() const;

	vector<Wall*>& getWallsGroup();

	vector<DrawingObject*>& getCoinsGroup();

	void updateCreaturesView(const vector<Creature*>& Creatures) const;
};

