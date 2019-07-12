#ifndef C_ACTION
#define C_ACTION

#include "inclusao.h"
#include "Event.h"
#include <iostream>

class Event;
class Action{

public:
	Action(Event&, float wait = -1);
	virtual ~Action();
	virtual void Execute();
	virtual bool GetStarted();
	virtual bool GetDone();
	virtual void Update(float);
	virtual bool Is(std::string) = 0;
  void Reset();
  void ChannelFinished(int channel);
protected:
	Event& associated;
	bool started;
	bool done;
  Timer* t;
};

#endif //C_ACTION
