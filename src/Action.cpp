#include "../include/Action.h"

Action::Action(Event &associated) : associated(associated) {}
Action::~Action(){}
void Action::Execute(){}
void Action::Update(float dt){}
bool Action::GetDone(){ return done; }
//bool Action::Is(std::string type){ return type == "Action";}
