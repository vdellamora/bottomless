#include "../include/Wait.h"
#include "../include/Game.h"
#include "../include/State.h"
#include "../include/EventMap.h"
#include "../include/Event.h"
#include "../include/Cecilia.h"

Wait::Wait(Event& associated, float miliseconds) : Action(associated){
	this->miliseconds = miliseconds;
	this->started = false;
	State tstate = Game::GetInstance().GetCurrentState();
	EventMap* em = (EventMap*) tstate.GetEventMap().GetComponent("EventMap");
	Event* e = em->GetEvent(associated.GetIdentifier());

	this->t = new Timer();
	// e->GetAssociated().AddComponent(t);

}
Wait::~Wait(){}
void Wait::Execute(){
	if(!started){ t->Restart(); started = true;}
	
}
void Wait::Update(float dt){
	if(started) t->Update(dt);
	if(t->Get() >= miliseconds) done = true;
}
bool Wait::Is(std::string type){return type == "Wait";}
