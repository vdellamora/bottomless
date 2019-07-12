#include "../include/GSwitch.h"
#include "../include/Game.h"
#include "../include/Event.h"

GSwitch::GSwitch(Event& associated, int pos, bool value, float wait) : Action(associated, wait){
	this->pos = pos;
	this->value = value;
}
GSwitch::~GSwitch(){
  if(t) delete t;
}
void GSwitch::Execute(){
  started = true;
	Game::VAR_GLOBAL[pos] = value;
  if (t == nullptr) done = true;
}
bool GSwitch::GetDone(){ return done; }
bool GSwitch::Is(std::string type){return type == "GSwitch";}
