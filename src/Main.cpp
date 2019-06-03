#include <iostream>
#include "../include/Game.h"
#include "../include/TitleState.h"

int main(int argc, char** argv){
	auto &j = Game::GetInstance();
	j.Push(new TitleState());
	j.Run();

	return 0;
}