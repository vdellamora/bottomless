#include <iostream>
#include "../include/Game.h"
#include "../include/TestState.h"
#include "../include/SubState.h"

int main(int argc, char** argv){
	auto &j = Game::GetInstance();
	j.Push(new SubState());
	j.Run();

	return 0;
}