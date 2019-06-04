#include <iostream>
#include "../include/Game.h"
#include "../include/TestState.h"

int main(int argc, char** argv){
	auto &j = Game::GetInstance();
	j.Push(new TestState());
	j.Run();

	return 0;
}