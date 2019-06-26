#include "../include/Empurravel.h"
#include "../include/Game.h"
#include "../include/TestState.h"
#include "../include/EventMap.h"
#include "../include/Event.h"
#include "../include/Move.h"

Empurravel::Empurravel(Event& associated) : Action(associated){}
Empurravel::~Empurravel(){}
void Empurravel::Execute(){
	TestState tstate = (TestState&) Game::GetInstance().GetCurrentState();
	EventMap* em = (EventMap*) tstate.GetEventMap().GetComponent("EventMap");

	em->RemoveEvent("Caranguejo");

	em->AddEvent("Caranguejo",8,6,0,true,6);
	em->GetEvent("Caranguejo")->NewAction(new Move(*(em->GetEvent("Caranguejo")), 0, 4));

	em->RemoveEvent("CaranguejoOuvido");
}
bool Empurravel::GetDone(){ return done;}
bool Empurravel::Is(std::string type){return type == "Empurravel";}
