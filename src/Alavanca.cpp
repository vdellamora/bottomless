#include "../include/Alavanca.h"
#include "../include/Game.h"
#include "../include/State.h"
#include "../include/EventMap.h"
#include "../include/Event.h"
#include "../include/Cecilia.h"

Alavanca::Alavanca(Event& associated) : Action(associated){
}
Alavanca::~Alavanca(){}
void Alavanca::Execute(){
  started = true;
  if (!done){
    State tstate = Game::GetInstance().GetCurrentState();
    EventMap* em = (EventMap*) tstate.GetEventMap().GetComponent("EventMap");
    Event* e1 = em->GetEvent("corneta1");
    Event* e2 = em->GetEvent("corneta2");
    Event* e3 = em->GetEvent("corneta3");
    
    e1->Execute();
    e2->Execute();
    e3->Execute();
    done = true;
  }
	
}
bool Alavanca::GetDone(){return done;}
bool Alavanca::Is(std::string type){return type == "Alavanca";}
