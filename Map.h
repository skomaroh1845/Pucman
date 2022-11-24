#pragma once


// It is a class of game map
class Map final
{
	char lvlmap[34][64];   // loads from file

public: 

	Map();

	void loadMap(const char* path);

	//...

};

