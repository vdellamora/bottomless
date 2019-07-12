#include "../include/Som.h"
#include "../include/Game.h"
#include "../include/TestState.h"
#include "../include/EventMap.h"
#include "../include/Event.h"
#include "../include/Cecilia.h"

Som::Som(Event& associated, int s, float wait) : Action(associated){
  if (wait >0){
    this->t = new Timer(wait);
  } else {
    this->t = nullptr;
  }
	id = s;	TRACE("som tst 1");
	TestState tstate = (TestState&) Game::GetInstance().GetCurrentState(); TRACE("som tst 2");
	EventMap* em = (EventMap*) tstate.GetEventMap().GetComponent("EventMap"); TRACE("som tst 3");
	Event* e = em->GetEvent(associated.GetIdentifier()); TRACE("som tst 4");
	switch(s){
		case 1:
			this->s = new Sound(e->GetAssociated(), "assets/audio/boom.wav");
			break;
		case 2:
			this->s = new Sound(e->GetAssociated(), "assets/audio/Shot1.wav");
			break;
		case 3:
			this->s = new Sound(e->GetAssociated(), "assets/audio/Shot2.wav");
			break;
		case 4:
			this->s = new Sound(e->GetAssociated(), "assets/audio/Shot3.wav");
			break;
		case 5:
			this->s = new Sound(e->GetAssociated(), "assets/audio/Failure1.wav");
			break;
	}
}
Som::~Som(){}
void Som::Execute(){
  started = true;
	if(Cecilia::player->GetGravando()){
		Cecilia::player->AddSound(id);
	}

	s->Play();
  channel = s->GetChannel(); // depois que pedir pra tocar guardar o canal que está tocando.
  if (t == nullptr) done = true;
	// Event* e = (Event*) associated.GetComponent("Event");
}
bool Som::GetDone(){return done;}
bool Som::Is(std::string type){return type == "Som";}
void Som::ChannelFinished(int channel){
  if (channel == this->channel){
    //se o canal que estava tocando terminou, fazer algo.
    
  }
};
