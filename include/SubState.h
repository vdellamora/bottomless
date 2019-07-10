#ifndef C_SUBSTATE
#define C_SUBSTATE

#include "inclusao.h"
#include "State.h"
#include <iostream>
#include <memory>

class SubState : public State{
  
public:
  SubState();
  ~SubState();
  void LoadAssets();
  void Update(float);
  void Render();
  void Start();
  void Pause();
  void Resume();
  
private:
  GameObject* cecilia;
  GameObject* crab;
  
};

#endif //C_SUBSTATE
