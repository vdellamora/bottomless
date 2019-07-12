#include "../include/Move.h"
#include "../include/Event.h"
#include "../include/Cecilia.h"

Move::Move(Event& associated, int direction, int speed) : Action(associated){
	this->direction = direction;
	this->speed = speed;
  
}
Move::~Move(){}
void Move::Execute(){
  if (!done){
    started = true;
    associated.Move(Cecilia::player->GetDirection(), speed);
    
    done = true;
  }
	// Event* e = (Event*) associated.GetComponent("Event");
}
//bool Move::GetDone(){return done;}
bool Move::Is(std::string type){return type == "Move";}
