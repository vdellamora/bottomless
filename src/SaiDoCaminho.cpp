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

	if(Game::VAR_GLOBAL[0]){
		State tstate = Game::GetInstance().GetCurrentState();
		EventMap* em = (EventMap*) tstate.GetEventMap().GetComponent("EventMap");

		TRACE("Move, desgraça");
		associated.Move(1, 4);
		// em->GetEvent("AguaViva")->ClearActions();
		em->GetEvent("AguaViva")->SetType(-1);
	}

	done = true;
}
bool SaiDoCaminho::Is(std::string type){return type == "SaiDoCaminho";}
