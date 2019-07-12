#include "../include/Action.h"

Action::Action(Event &associated, float wait) : associated(associated) {
  started = false;
  done = false;
  if (wait > 0) t = new Timer(wait);
  else t = nullptr;
}

Action::~Action(){}
void Action::Execute(){}
void Action::Update(float dt){
  if (t){
    t->Update(dt);
    if (t->Finished()) done = true;
  }
}
bool Action::GetStarted(){ return started; }
bool Action::GetDone(){ return done; }
void Action::Reset(){started = false; done = false;}
void Action::ChannelFinished(int channel){};
//bool Action::Is(std::string type){ return type == "Action";}
