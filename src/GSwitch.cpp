#include "../include/GSwitch.h"
#include "../include/Game.h"
#include "../include/Event.h"

GSwitch::GSwitch(Event& associated, int pos, bool value) : Action(associated){
	this->pos = pos;
	this->value = value;
}
GSwitch::~GSwitch(){}
void GSwitch::Execute(){
	Game::VAR_GLOBAL[pos] = value;
	done = true;
}
bool GSwitch::GetDone(){return done;}
bool GSwitch::Is(std::string type){return type == "GSwitch";}
