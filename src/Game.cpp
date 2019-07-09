#include "../include/Game.h"
#include "../include/InputManager.h"
#include <ctime>
#include <memory>

bool Game::VAR_GLOBAL[10];
Game* Game::instance = nullptr;

Game& Game::GetInstance(){
	if(instance != nullptr) return *instance;
	instance = new Game("Bottomless", 1280, 720);
	return *instance;
}

Game::Game(std::string title, int width, int height){
	//VAR_GLOBAL VARIAVEIS:
	Game::VAR_GLOBAL[0] = false; //0 - Pronto para tocar corneta 3


	std::srand(time(NULL));
	dt = 0;
	frameStart = 0;

	if(instance == nullptr){
		instance = this;
	} else {
		// Tratar erro
	}

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)){
		// Tratar erro
		//SDL_GetError
	}

	if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)==0){
		// Tratar erro
	}

	if(Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3)==0){
		// Tratar erro
	}
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, 
		MIX_DEFAULT_FORMAT, 
		MIX_DEFAULT_CHANNELS, 
		1024)){
		// Tratar erro
	}
	if(TTF_Init() == 0){
		//Tratar erro
	}
	//if(Mix_AllocateChannels(2)){}
	////////////////////////////////////////////////////////////

	window = SDL_CreateWindow(title.c_str(), 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		width, height, 0);
	renderer = SDL_CreateRenderer(window,
		-1,
		SDL_RENDERER_ACCELERATED);
	storedState = nullptr;
}

Game::~Game(){
	if (storedState != nullptr) delete storedState;
	TTF_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::Push(State* state){storedState = state;}
State& Game::GetCurrentState(){ return *(std::unique_ptr<State> &)stateStack.top();}

float Game::GetDeltaTime(){ return dt;}

void Game::CalculateDeltaTime(){
	int ticks = SDL_GetTicks();
	dt = (ticks - frameStart) / 1000.0f;
	frameStart = ticks;
	// TRACE("CalculateDeltaTime " + ticks);
}

SDL_Renderer* Game::GetRenderer(){
	return renderer;
}

void Game::Run(){
	if(storedState != nullptr){
		stateStack.emplace(storedState);
		storedState = nullptr;
		
		GetCurrentState().Start();
		while(!stateStack.empty() && !GetCurrentState().QuitRequested()){
			if (GetCurrentState().PopRequested()){
				TRACE("Game pediu POP");
				stateStack.pop();
				TRACE("Game deu POP");
				Resources::ClearImages(); TRACE("Game ClearImages");
				Resources::ClearSounds(); TRACE("Game ClearSounds");
				Resources::ClearMusics(); TRACE("Game ClearMusics");
				Resources::ClearFonts(); TRACE("Game ClearFonts");

				TRACE("Game limpou Resources");
				if(!stateStack.empty()) GetCurrentState().Resume();
				TRACE("Game passou do if");
			}

			if (storedState != nullptr){
				TRACE("Game pediu novo STATE");
				if(!stateStack.empty()) GetCurrentState().Pause();
				stateStack.emplace(storedState);
				storedState = nullptr;
				GetCurrentState().Start();
			}

			if (stateStack.empty()) break;
			CalculateDeltaTime();
			InputManager::GetInstance().Update();
			GetCurrentState().Update(dt);
			GetCurrentState().Render();

			SDL_RenderPresent(renderer);
			SDL_Delay(33);
		}
		
	} else {
		// Tratar erro
		std::cout << "Não consegui abrir o estado atual." << std::endl;
		exit(1);
	}
	Resources::ClearImages(); Resources::ClearMusics();
	Resources::ClearSounds(); Resources::ClearFonts();
}