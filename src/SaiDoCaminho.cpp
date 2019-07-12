#include "../include/SaiDoCaminho.h"
#include "../include/SaiDoCaminho.h"
#include "../include/Game.h"
#include "../include/State.h"
#include "../include/EventMap.h"
#include "../include/Event.h"
// #include "../include/Move.h"

SaiDoCaminho::SaiDoCaminho(Event& associated) : Action(associated){}
SaiDoCaminho::~SaiDoCaminho(){}
void SaiDoCaminho::Execute(){
	started = true;

	State tstate = Game::GetInstance().GetCurrentState();
	EventMap* em = (EventMap*) tstate.GetEventMap().GetComponent("EventMap");

	// associated.Move(1, 0);
	em->GetEvent("AguaViva")->ClearActions();

	done = true;
}
bool SaiDoCaminho::Is(std::string type){return type == "SaiDoCaminho";}
