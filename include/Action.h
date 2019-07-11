#ifndef C_ACTION
#define C_ACTION

#include "inclusao.h"
#include "Event.h"
#include <iostream>

class Event;
class Action{

public:
	Action(Event&);
	virtual ~Action();
	virtual void Execute();
	virtual bool GetStarted();
	virtual bool GetDone();
	virtual void Update(float);
	virtual bool Is(std::string) = 0;
protected:
	Event& associated;
	bool started;
	bool done;
};

#endif //C_ACTION
