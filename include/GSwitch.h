#ifndef C_GSWITCH
#define C_GSWITCH

#include "inclusao.h"
#include "Event.h"
#include "Component.h"
#include "Action.h"
#include <iostream>

class Event;
class GSwitch : public Action{

public:
	GSwitch(Event&, int, bool, float wait = -1);
	~GSwitch();
	void Execute();
	bool GetDone();
	bool Is(std::string);
private:
	int pos;
	bool value;
};

#endif //C_GSWITCH
