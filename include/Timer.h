#ifndef C_TIMER
#define C_TIMER

#include "inclusao.h"
#include <iostream>

class Timer{

public:
	Timer();
	void Update(float);
	void Restart();
	float Get();
private:
	float time;
};

#endif //C_TIMER