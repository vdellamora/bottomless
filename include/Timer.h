#ifndef C_TIMER
#define C_TIMER

#include "inclusao.h"
#include <iostream>

class Timer{

public:
  Timer();
	Timer(float finish);
	void Update(float);
	void Restart();
	float Get();
  bool Finished();
private:
	float time;
  float finish;
};

#endif //C_TIMER
