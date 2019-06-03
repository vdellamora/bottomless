#ifndef C_CAMERA
#define C_CAMERA

#include "inclusao.h"
#include "GameObject.h"
#include "Vec2.h"
#include <iostream>

class Camera{

public:
	static void Update(float);
	static void Follow(GameObject*);
	static void Unfollow();
	static Vec2 pos;
	static Vec2 speed;
private:
	static GameObject* focus;
};

#endif //C_CAMERA