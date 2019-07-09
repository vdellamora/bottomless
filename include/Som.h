#ifndef C_SOM
#define C_SOM

#include "inclusao.h"
#include "Event.h"
#include "Action.h"
#include "Sound.h"
#include <iostream>

class Event;
class Som : public Action{

public:
	Som(Event&, int);
	~Som();
	void Execute();
	bool GetDone();
	bool Is(std::string);
private:
	Sound* s;
	int id;
};

#endif //C_SOM