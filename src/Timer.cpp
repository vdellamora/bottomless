#include "../include/Timer.h"

Timer::Timer(){ time = 0; finish = 0xFFFFFF; }//manter funcionamento normal;
Timer::Timer(float f){ time = 0; finish = f; }
void Timer::Update(float dt){ time+=dt; }
void Timer::Restart(){ time = 0; }
float Timer::Get(){ return time; }
bool Timer::Finished(){return time > finish; }
