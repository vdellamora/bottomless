#ifndef C_INPUTMANAGER
#define C_INPUTMANAGER

#include "inclusao.h"
#include <iostream>
#include <unordered_map>

#define W_KEY				SDLK_w
#define A_KEY				SDLK_a
#define S_KEY				SDLK_s
#define D_KEY				SDLK_d
#define LEFT_ARROW_KEY		SDLK_LEFT
#define RIGHT_ARROW_KEY		SDLK_RIGHT
#define UP_ARROW_KEY		SDLK_UP
#define DOWN_ARROW_KEY		SDLK_DOWN
#define ESCAPE_KEY			SDLK_ESCAPE
#define SPACE_KEY			SDLK_SPACE
#define LEFT_MOUSE_BUTTON	SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON	SDL_BUTTON_RIGHT

class InputManager{

public:
	void Update();
	bool KeyPress(int);
	bool KeyRelease(int);
	bool IsKeyDown(int);
	bool MousePress(int);
	bool MouseRelease(int);
	bool IsMouseDown(int);
	int GetMouseX();
	int GetMouseY();
	bool QuitRequested();
	static InputManager& GetInstance();
	InputManager();
	~InputManager();
private:
	bool mouseState[6];
	int mouseUpdate[6];

	std::unordered_map<int, bool> keyState;
	std::unordered_map<int, int> keyUpdate;

	bool quitRequested;
	int updateCounter;

	int mouseX;
	int mouseY;

};

#endif //C_INPUTMANAGER