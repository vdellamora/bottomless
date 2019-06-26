#ifndef C_EMPURRAVEL
#define C_EMPURRAVEL

#include "inclusao.h"
#include "Event.h"
#include "Component.h"
#include "Action.h"
#include <iostream>

class Event;
class Empurravel : public Action{

public:
	Empurravel(Event&);
	~Empurravel();
	void Execute();
	bool GetDone();
	bool Is(std::string);
private:
};

#endif //C_EMPURRAVEL