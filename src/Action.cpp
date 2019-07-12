#include "../include/Action.h"

Action::Action(Event &associated) : associated(associated) { started = false; done = false;}
Action::~Action(){}
void Action::Execute(){}
void Action::Update(float dt){}
bool Action::GetStarted(){ return started; }
bool Action::GetDone(){ return done; }
void Action::Reset(){started = false; done = false;}
//bool Action::Is(std::string type){ return type == "Action";}
