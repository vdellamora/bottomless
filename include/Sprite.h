#ifndef C_SPRITE
#define C_SPRITE

#include "inclusao.h"
#include "Component.h"
#include "Vec2.h"
#include "Timer.h"
#include <iostream>
#include <memory>

class Sprite : public Component{

public:
	explicit Sprite(GameObject&);
	explicit Sprite(GameObject&, std::string, int = 1, float = 1, float = 0);
	~Sprite();
	void NewSprite(std::string, int = 1, float = 1, float = 0);
	void Open(std::string);
	void SetFrame(int);
	void SetFrameCount(int);
	void SetFrameTime(float);
	void SetClip(int, int, int, int);
	void SetScaleX(float, float);
	void Update(float);
	void Render();
	void Render(float, float);
	int GetWidth();
	int GetHeight();
	bool GetFlip();
	void SetFlip(bool);
	Vec2 GetScale();
	bool Is(std::string);
	bool IsOpen();
	float angleDeg;
private:
	std::shared_ptr<SDL_Texture> texture;
	int frameCount;
	int currentFrame;
	float timeElapsed;
	float frameTime;
	int width;
	int height;
	bool flip;
	Vec2 scale;
	Timer selfDestructCount;
	float secondsToSelfDestruct;
	SDL_Rect clipRect;

};

#endif //C_SPRITE