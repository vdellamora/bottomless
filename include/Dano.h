#ifndef C_DANO
#define C_DANO

#include "inclusao.h"
#include "Event.h"
#include "Component.h"
#include "Action.h"
#include <iostream>

class Event;
class Dano : public Action{

public:
	Dano(Event&, int);
	~Dano();
	void Execute();
	bool GetDone();
	bool Is(std::string);
private:
	int quantidade;
};

#endif //C_DANO