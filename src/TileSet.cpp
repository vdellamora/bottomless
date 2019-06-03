#include "../include/TileSet.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file){
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	tileSet = new Sprite(*(new GameObject()), file);
	columns = tileSet->GetWidth()/this->tileWidth;
	rows = tileSet->GetHeight()/this->tileHeight;
}
TileSet::~TileSet(){}

void TileSet::RenderTile(unsigned index, float x, float y){
	// TRACE("RenderTile");
	if((index >= 0) && (index < (rows*columns - 1))){
		tileSet->SetClip(
			((index%columns))*tileWidth, 
			((index/columns))*tileHeight,
			 tileWidth, tileHeight);
		tileSet->Render(x, y);
	}
}

int TileSet::GetTileWidth(){ return tileWidth;}
int TileSet::GetTileHeight(){ return tileHeight;}
