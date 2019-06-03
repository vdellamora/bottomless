#include <iostream>
#include "../include/Music.h"


	Music::Music(){ music = nullptr; }
	Music::Music(std::string file){
		//music = nullptr;
		Open(file);
	}
	Music::~Music(){
		Stop(0);
	}
	void Music::Play(int times){
		if(music != nullptr) Mix_PlayMusic(music.get(), times);
		else {
			// Tratar erro
			std::cout << "Erro: Não há música nesta instância. Detalhes: " << SDL_GetError() << std::endl;
			exit(1);
		}

	}
	void Music::Stop(int msToStop){ Mix_FadeOutMusic(msToStop); }
	void Music::Open(std::string file){
		music = Resources::GetMusic(file);
	}
	bool Music::IsOpen(){ return (music!=nullptr); }
