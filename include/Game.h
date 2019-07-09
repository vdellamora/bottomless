#ifndef C_GAME
#define C_GAME

#include "inclusao.h"
#include <iostream>
#include <stack>
#include "State.h"
#include "Resources.h"

class State;
class Game{

public:
	Game(std::string, int, int);
	~Game();
	static Game& GetInstance();
	SDL_Renderer* GetRenderer();
	State& GetCurrentState();
	void Push(State*);
	void Run();
	float GetDeltaTime();

	static bool VAR_GLOBAL[10];
private:
	void CalculateDeltaTime();
	int frameStart;
	float dt;
	static Game* instance;
	State* storedState;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::stack<std::unique_ptr<State> > stateStack;


};

#endif //C_GAME