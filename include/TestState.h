#ifndef C_TESTSTATE
#define C_TESTSTATE

#include "inclusao.h"
#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include <iostream>
#include <memory>

class TestState : public State{

public:
	TestState();
	~TestState();
	void LoadAssets();
	void Update(float);
	void Render();
	void Start();
	void Pause();
	void Resume();

	GameObject& GetCollisionMap();
private:
	GameObject* bg;
	GameObject* tm;
	GameObject* cm;
	GameObject* cecilia;
	Music music;

};

#endif //C_TESTSTATE