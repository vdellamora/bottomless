#include "../include/Sound.h"

Sound::Sound(GameObject& associated) : Component(associated){
	this->associated = associated;
	chunk = nullptr;
}
Sound::Sound(GameObject& associated, std::string file) : Component(associated){
	this->associated = associated;
	Open(file);
}
Sound::~Sound(){
	Stop();
	// if (IsOpen()) Mix_FreeChunk(chunk);
}
void Sound::Update(float dt){}
void Sound::Render(){}
void Sound::Play(int times){
	channel = Mix_PlayChannel(-1, chunk.get(), times-1);
	if(channel == -1){
		std::cout << "Erro: Não consegui tocar o som. Detalhes: " << SDL_GetError() << std::endl;
		exit(1);
	}
}
void Sound::Stop(){
	if (IsOpen()) Mix_HaltChannel(channel);
}
void Sound::Open(std::string file){
	chunk = Resources::GetSound(file);
}

bool Sound::IsOpen(){ return (chunk!=nullptr); }
bool Sound::IsPlaying(){ return Mix_Playing(this->channel); }
bool Sound::Is(std::string type){ return type == "Sound"; };
