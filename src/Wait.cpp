#include "../include/Wait.h"
#include "../include/Game.h"
#include "../include/State.h"
#include "../include/EventMap.h"
#include "../include/Event.h"
#include "../include/Cecilia.h"

Wait::Wait(Event& associated, float miliseconds) : Action(associated){
	this->miliseconds = miliseconds;
	this->start = false;
	State tstate = Game::GetInstance().GetCurrentState();
	EventMap* em = (EventMap*) tstate.GetEventMap().GetComponent("EventMap");
	Event* e = em->GetEvent(associated.GetIdentifier());

	this->t = new Timer();
	// e->GetAssociated().AddComponent(t);

}
Wait::~Wait(){}
void Wait::Execute(){
	if(!start){ t->Restart(); start = true;}
	
}
void Wait::Update(float dt){
	if(start) t->Update(dt);
	if(t->Get() >= miliseconds) done = true;
}
bool Wait::GetDone(){return done;}
bool Wait::Is(std::string type){return type == "Wait";}
