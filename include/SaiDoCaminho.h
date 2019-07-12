#ifndef C_SAIDOCAMINHO
#define C_SAIDOCAMINHO

#include "inclusao.h"
#include "Event.h"
#include "Component.h"
#include "Action.h"
#include <iostream>

class Event;
class SaiDoCaminho : public Action{

public:
	SaiDoCaminho(Event&);
	~SaiDoCaminho();
	void Execute();
	bool Is(std::string);
private:
};

#endif //C_SAIDOCAMINHO