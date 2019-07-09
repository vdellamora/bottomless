#ifndef C_ALAVANCA
#define C_ALAVANCA

#include "inclusao.h"
#include "Event.h"
#include "Component.h"
#include "Action.h"
#include <iostream>

class Event;
class Alavanca : public Action{

public:
	Alavanca(Event&);
	~Alavanca();
	void Execute();
	bool GetDone();
	bool Is(std::string);
private:
};

#endif //C_ALAVANCA