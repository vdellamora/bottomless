#include "../include/TileMap.h"
#include "../include/Camera.h"
#include <fstream>

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : Component(associated){
	this->tileSet = tileSet;
	Load(file);
}
TileMap::~TileMap(){}
void TileMap::Load(std::string file){
	std::ifstream entrada (file.c_str());
	std::string linha;
	std::getline(entrada, linha); // pega primeira linha
	std::stringstream ssc(linha);
	std::string temp;
	std::getline(ssc, temp, ',');
	mapWidth = std::atoi(temp.c_str());
	std::getline(ssc, temp, ',');
	mapHeight = std::atoi(temp.c_str());
	std::getline(ssc, temp, ',');
	mapDepth = std::atoi(temp.c_str());

	///// Trace
	TRACE(mapWidth << " " << mapHeight << " " << mapDepth);

	associated.box.w = mapWidth*tileSet->GetTileWidth();
	associated.box.h = mapHeight*tileSet->GetTileHeight();

	// Pegou tamanho do mapa
	std::getline(entrada, linha);

	for(int k = 0; k < mapDepth; k++){
		for(int i = 0; i < mapHeight; i++){
			std::getline(entrada, linha);
			std::stringstream ssc(linha);
			for(int j = 0; j < mapWidth; j++){
				std::getline(ssc, temp, ',');
				int valor = std::atoi(temp.c_str())-1;
				tileMatrix.push_back(valor);
				//tileMatrix[i][j][k] = std::atoi(temp) - 1;

				///// Trace
				//TRACEN( ((valor<10 && valor >= 0) ? " " : "") + std::to_string(valor) + " ");
			}
			//TRACEN("\n");
		}
		//TRACEN("\n");
		std::getline(entrada, linha);
	}
}
void TileMap::SetTileSet(TileSet* tileSet){
	this->tileSet = tileSet;
}
int& TileMap::At(int x, int y, int z){
	return tileMatrix[z*mapWidth*mapHeight + y*mapWidth + x]; 
	//return &tileMatrix[x][y][z];
}
void TileMap::AlteraTile(int x, int y, int z, int tile){
	tileMatrix[z*mapWidth*mapHeight + y*mapWidth + x] = tile;
}
void TileMap::Render(){
	for(int i = 0; i<mapDepth; i++){
		RenderLayer(i, Camera::pos.x, Camera::pos.y);
	}
}
void TileMap::Render(int layer){
	RenderLayer(layer, Camera::pos.x, Camera::pos.y);
}
void TileMap::RenderLayer(int layer, int cameraX = 0, int cameraY = 0){
	// TRACE("RenderLayer");

	for(int i = 0; i < mapWidth; i++){
		for(int j = 0; j < mapHeight; j++){
			int posX, posY;
			posX = i * tileSet->GetTileWidth()  - cameraX * layer/3;
			posY = j * tileSet->GetTileHeight() - cameraY * layer/3;
			// TRACE(cameraX << " " << cameraY);
			// TRACE("PosX PosY: " << posX << " " << posY);
			// TRACE("TSw TSh: " << -tileSet->GetTileWidth() << " " << -tileSet->GetTileHeight());
			// TRACE("BoxW BoxH: " << associated.box.w << " " << associated.box.h);
			if(
				(posX) > -tileSet->GetTileWidth() &&
				(posX) < associated.box.w  &&
				(posY) > -tileSet->GetTileHeight() &&
				(posY) < associated.box.h
			){
				tileSet->RenderTile(At(i, j, layer), 
					posX, 
					posY);
			}
		}
	}
}
bool TileMap::Is(std::string type){ if(type=="TileMap") return true; return false;}
int TileMap::GetWidth(){ return mapWidth;}
int TileMap::GetHeight(){ return mapHeight;}
int TileMap::GetDepth(){ return mapDepth;}
