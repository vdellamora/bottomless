#ifndef C_SOUND
#define C_SOUND

#include "inclusao.h"
#include "Component.h"
#include "GameObject.h"
#include "Resources.h"
#include <iostream>
#include <memory>

class Sound : public Component{

public:
	Sound(GameObject&);
	Sound(GameObject&, std::string);
	~Sound();
	void Update(float);
	void Render();
	void Play(int = 1);
	void Stop();
	void Open(std::string);
	bool IsPlaying();
	bool IsOpen();
	bool Is(std::string);
private:
	std::shared_ptr<Mix_Chunk> chunk;
	int channel;
};

#endif //C_SOUND