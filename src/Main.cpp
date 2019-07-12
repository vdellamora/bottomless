#include <iostream>
#include "../include/Game.h"
#include "../include/TestState.h"
#include "../include/SubState.h"

// a simple channel_finished function
void channelDone(int channel) {
  printf("channel %d finished playback.\n",channel);
}

int main(int argc, char** argv){
  // set the callback for when a channel stops playing
  Mix_ChannelFinished(channelDone);
	auto &j = Game::GetInstance();
	j.Push(new TestState());
	j.Run();

	return 0;
}
