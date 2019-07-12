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
	Som(Event&, int, float wait = -1);
	~Som();
	void Execute();
	bool GetDone();
	bool Is(std::string);
  void ChannelFinished(int channel);
private:
	Sound* s;
	int id;
  int channel;
};

#endif //C_SOM
