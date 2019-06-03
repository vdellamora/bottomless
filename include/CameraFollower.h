#ifndef C_CAMERAFOLLOWER
#define C_CAMERAFOLLOWER

#include "inclusao.h"
#include "GameObject.h"
#include <iostream>

class GameObject;
class CameraFollower : public Component{

public:
	CameraFollower(GameObject&);
	~CameraFollower();
	void Update(float);
	void Render();
	bool Is(std::string);
};

#endif //C_CAMERAFOLLOWER