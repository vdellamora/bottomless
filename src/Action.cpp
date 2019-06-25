#include "../include/Action.h"

Action::Action(Event &associated) : associated(associated) {}
Action::~Action(){}
void Action::Execute(){}
bool Action::GetDone(){}
bool Action::Is(std::string type){}
