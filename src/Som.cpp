#include "../include/Som.h"
#include "../include/Game.h"
#include "../include/TestState.h"
#include "../include/EventMap.h"
#include "../include/Event.h"
#include "../include/Cecilia.h"

Som::Som(Event& associated, int s) : Action(associated){
	id = s;	TRACE("som tst 1");
	TestState tstate = (TestState&) Game::GetInstance().GetCurrentState(); TRACE("som tst 2");
	EventMap* em = (EventMap*) tstate.GetEventMap().GetComponent("EventMap"); TRACE("som tst 3");
	Event* e = em->GetEvent(associated.GetIdentifier()); TRACE("som tst 4");
	switch(s){
		case 1:
			this->s = new Sound(e->GetAssociated(), "assets/audio/boom.wav");
			break;
		case 2:
			this->s = new Sound(e->GetAssociated(), "assets/audio/boom.wav");
			break;
		case 3:
			this->s = new Sound(e->GetAssociated(), "assets/audio/boom.wav");
			break;
		case 4:
			this->s = new Sound(e->GetAssociated(), "assets/audio/boom.wav");
			break;
		case 5:
			this->s = new Sound(e->GetAssociated(), "assets/audio/boom.wav");
			break;
	}
}
Som::~Som(){}
void Som::Execute(){
	if(Cecilia::player->GetGravando()){
		Cecilia::player->AddSound(id);
	}

	s->Play();
	done = true;
	// Event* e = (Event*) associated.GetComponent("Event");
}
bool Som::GetDone(){return done;}
bool Som::Is(std::string type){return type == "Som";}