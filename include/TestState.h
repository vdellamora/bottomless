#ifndef C_TESTSTATE
#define C_TESTSTATE

#include "inclusao.h"
#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "TileSet.h"
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
private:
	GameObject* bg;
	GameObject* cecilia;
	GameObject* crab;
	TileSet* ts;
	Music music;

};

#endif //C_TESTSTATE