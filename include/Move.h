#ifndef C_MOVE
#define C_MOVE

#include "inclusao.h"
#include "Event.h"
#include "Component.h"
#include "Action.h"
#include <iostream>

class Event;
class Move : public Action{

public:
	Move(Event&, int, int);
	~Move();
	void Execute();
//  bool GetDone();
	bool Is(std::string);
private:
	int direction;
	int speed;
};

#endif //C_MOVE
