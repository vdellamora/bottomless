#ifndef C_MUSIC
#define C_MUSIC

#define NOGDI
#include "inclusao.h"
#include "Resources.h"
#include <iostream>
#include <memory>

class Music{

public:
	Music();
	Music(std::string);
	~Music();
	void Play(int = -1);
	void Stop(int  = 1500);
	void Open(std::string);
	bool IsOpen();
private:
	std::shared_ptr<Mix_Music> music;
};

#endif //C_MUSIC