#include <iostream>
#include "../include/Game.h"
#include "../include/TestState.h"
#include "../include/SubState.h"
#include "../include/Cecilia.h"

// a simple channel_finished function
void channelDone(int channel) {
  TRACE("channel " + TST(channel) + " finished playback.\n");
  Game::GetInstance();
//  Cecilia::player->
}

int main(int argc, char** argv){
  // set the callback for when a channel stops playing
  Mix_ChannelFinished(channelDone);
	auto &j = Game::GetInstance();
	j.Push(new TestState());
	j.Run();

	return 0;
}
