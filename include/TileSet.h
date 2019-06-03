#ifndef C_TILESET
#define C_TILESET

#include "inclusao.h"
#include "Sprite.h"
#include "GameObject.h"
#include <iostream>

class TileSet{

public:
	TileSet(int, int, std::string);
	~TileSet();
	void RenderTile(unsigned, float, float);
	int GetTileWidth();
	int GetTileHeight();
private:
	Sprite* tileSet;
	int rows;
	int columns;
	int tileWidth;
	int tileHeight;

};

#endif //C_TILESET