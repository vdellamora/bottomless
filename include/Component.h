#ifndef C_COMPONENT
#define C_COMPONENT

#include "inclusao.h"
#include "GameObject.h"
#include <iostream>

class GameObject;
class Component{

public:
	Component(GameObject&);
	virtual ~Component();
	virtual void Start();
	virtual void Update(float);
	virtual void Render();
	virtual void NotifyCollision(GameObject&);
	virtual bool Is(std::string);
protected:
	GameObject& associated;
};

#endif //C_COMPONENT