#ifndef C_WAIT
#define C_WAIT

#include "inclusao.h"
#include "Event.h"
#include "Component.h"
#include "Action.h"
#include "Timer.h"
#include <iostream>

class Event;
class Wait : public Action{

public:
	Wait(Event&, float);
	~Wait();
	void Execute();
	void Update(float);
	bool Is(std::string);
private:
	float seconds;
	Timer* t;
};

#endif //C_WAIT
