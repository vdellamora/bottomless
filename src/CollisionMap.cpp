#include "../include/CollisionMap.h"
#include <fstream>

CollisionMap::CollisionMap(GameObject& associated, std::string file) : Component(associated){
	Load(file);
}
void CollisionMap::Load(std::string file){
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

	TRACE(mapWidth << " " << mapHeight << " " << mapDepth);

	// Pegou tamanho do mapa
	std::getline(entrada, linha);

	for(int k = 0; k < mapDepth; k++){
		for(int i = 0; i < mapHeight; i++){
			std::getline(entrada, linha);
			std::stringstream ssc(linha);
			for(int j = 0; j < mapWidth; j++){
				std::getline(ssc, temp, ',');
				int valor = std::atoi(temp.c_str());
				collisionMatrix.push_back(valor);
				//collisionMatrix[i][j][k] = std::atoi(temp);

				TRACEN( ((valor<10 && valor >= 0) ? " " : "") + std::to_string(valor) + " ");
			}
			TRACEN("\n");
		}
		TRACEN("\n");
		std::getline(entrada, linha);
	}
}
int& CollisionMap::At(int x, int y, int z){
	int conta = z*mapWidth*mapHeight + y*mapWidth + x;
	int falho = 1;
	if(conta>collisionMatrix.size()) return falho;
	return collisionMatrix[conta]; 
	//return &collisionMatrix[x][y][z];
}

bool CollisionMap::Is(std::string type){ return (type == "CollisionMap");}
int CollisionMap::GetWidth(){ return mapWidth;}
int CollisionMap::GetHeight(){ return mapHeight;}
int CollisionMap::GetDepth(){ return mapDepth;}
void CollisionMap::Render(){}
CollisionMap::~CollisionMap(){}
