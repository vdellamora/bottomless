#ifndef C_COLLIDER
#define C_COLLIDER

#include "inclusao.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Rect.h"
#include <iostream>

class GameObject;
class Collider : public Component{

public:
	Collider(GameObject&, Vec2 = {1,1}, Vec2 = {0,0});
	~Collider();
	Rect box;
	void Update(float);
	void Render();
	bool Is(std::string);
	void SetScale(Vec2);
	void SetOffset(Vec2);
private:
	Vec2 scale;
	Vec2 offset;
};

#endif //C_COLLIDER