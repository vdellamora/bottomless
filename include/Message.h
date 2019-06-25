#ifndef C_MESSAGE
#define C_MESSAGE

#include "inclusao.h"
#include "Action.h"
#include "Event.h"
#include <iostream>

class Event;
class Message : public Action{

public:
	Message(Event&, std::string);
	~Message();
	void Execute();
	bool GetDone();
	bool Is(std::string);
private:
	std::string text;
};

#endif //C_MESSAGE