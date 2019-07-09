#ifndef C_COLLISIONMAP
#define C_COLLISIONMAP

#include "inclusao.h"
#include "Component.h"
#include <iostream>
#include <sstream>

class CollisionMap : public Component{

public:
	CollisionMap(GameObject&, std::string);
	~CollisionMap();
	void Load(std::string);
	int& At(int, int, int);
	void AlteraTile(int, int, int, int);

	void Render();

	bool Is(std::string);
	int GetWidth();
	int GetHeight();
	int GetDepth();
private:
	std::vector<int> collisionMatrix;
	//std::vector<vector<vector<int>>> tileMatrix;
	int mapWidth;
	int mapHeight;
	int mapDepth;
};

#endif //C_COLLISIONMAP