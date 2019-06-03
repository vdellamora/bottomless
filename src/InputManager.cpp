#include "../include/InputManager.h"

void InputManager::Update(){
	// TRACE("InputManagerUpdate");

	SDL_Event event;
	SDL_GetMouseState(&mouseX, &mouseY);
	quitRequested = false;
	updateCounter++;

	while(SDL_PollEvent(&event)){
		//TRACE("InputManagerUpdate - while " + std::to_string(event.type));
		switch(event.type){
			case SDL_QUIT:
				quitRequested = true;
				break;
			case SDL_KEYUP:
			case SDL_KEYDOWN:
				if(!event.key.repeat){
					//TRACEN("key ");
					//TRACE(std::to_string(event.key.keysym.sym));
					keyState[event.key.keysym.sym] = event.type == SDL_KEYDOWN;
					keyUpdate[event.key.keysym.sym] = updateCounter;
				}
				break;
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
				//TRACEN("mouse ");
				//TRACE(std::to_string(event.button.button));
				mouseState[event.button.button] = event.type == SDL_MOUSEBUTTONDOWN;
				mouseUpdate[event.button.button] = updateCounter;
				break;

		}
	}
}

//// TECLADO ////////////////////////////

bool InputManager::KeyPress(int key){
	return keyState[key] && (keyUpdate[key] == updateCounter);
}
bool InputManager::KeyRelease(int key){
	return !keyState[key] && (keyUpdate[key] == updateCounter);
}
bool InputManager::IsKeyDown(int key){ return keyState[key];}

////// MOUSE ////////////////////////////////

bool InputManager::MousePress(int button){
	return mouseState[button] && (mouseUpdate[button] == updateCounter);
}
bool InputManager::MouseRelease(int button){
	return !mouseState[button] && (mouseUpdate[button] == updateCounter);
}
bool InputManager::IsMouseDown(int button){ return mouseState[button];}


int InputManager::GetMouseX(){ return mouseX; }
int InputManager::GetMouseY(){ return mouseY; }
bool InputManager::QuitRequested(){ return quitRequested; }

InputManager& InputManager::GetInstance(){
	static InputManager im;
	return im;
}

InputManager::InputManager(){
	TRACE("InputManager");
	MSET(mouseState, 0);
	MSET(mouseUpdate, 0);
	quitRequested = false;
	updateCounter = 0;
	mouseX = 0;
	mouseY = 0;
}
InputManager::~InputManager(){}
