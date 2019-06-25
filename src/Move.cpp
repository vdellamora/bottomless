#include "../include/Move.h"
#include "../include/Event.h"
#include "../include/Cecilia.h"

Move::Move(Event& associated, int direction, int speed) : Action(associated){
	this->direction = direction;
	this->speed = speed;
}
Move::~Move(){}
void Move::Execute(){
	// Event* e = (Event*) associated.GetComponent("Event");
	associated.Move(Cecilia::player->GetDirection(), speed);
}
bool Move::GetDone(){}
bool Move::Is(std::string type){return type == "Move";}
