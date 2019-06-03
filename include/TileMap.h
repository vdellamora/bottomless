#ifndef C_TILEMAP
#define C_TILEMAP

#include "inclusao.h"
#include "Component.h"
#include "TileSet.h"
#include <iostream>
#include <sstream>

class TileSet;
class TileMap : public Component{

public:
	TileMap(GameObject&, std::string, TileSet*);
	~TileMap();
	void Load(std::string);
	void SetTileSet(TileSet*);
	int& At(int, int, int);
	void Render();
	void Render(int);
	void RenderLayer(int, int, int);
	bool Is(std::string);
	int GetWidth();
	int GetHeight();
	int GetDepth();
private:
	std::vector<int> tileMatrix;
	//std::vector<vector<vector<int>>> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;

};

#endif //C_TILEMAP