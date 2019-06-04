#include "../include/Game.h"
#include "../include/Rect.h"
#include "../include/Sprite.h"
#include "../include/Resources.h"
#include "../include/Camera.h"

Sprite::Sprite(GameObject& go) : Component(go) {
	texture = nullptr;	angleDeg = 0;
	scale.x = 1.0f; scale.y = 1.0f;
}
Sprite::Sprite(GameObject& go, std::string file, int frameCount, float frameTime, float secondsToSelfDestruct) : Component(go){
	// TRACE("Sprite::Sprite");
	NewSprite(file, frameCount, frameTime, secondsToSelfDestruct);
}
void Sprite::NewSprite(std::string file, int frameCount, float frameTime, float secondsToSelfDestruct){
	flip = false;
	this->frameCount = frameCount;
	this->frameTime = frameTime;
	this->secondsToSelfDestruct = secondsToSelfDestruct;
	selfDestructCount = Timer();
	texture = nullptr;	angleDeg = 0;
	scale.x = 1.0f; scale.y = 1.0f;
	Open(file);
}
void Sprite::Open(std::string file){
	// if(frameCount != 1) TRACE(width/frameCount);
	texture = Resources::GetImage(file);
	SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
	associated.box.w = GetWidth();
	associated.box.h = GetHeight();
	SetClip(0, 0, width/frameCount, height);
}
void Sprite::SetClip(int x, int y, int w, int h){
	// TRACE("Sprite::SetClip");
	clipRect.x = x;	clipRect.y = y;
	clipRect.w = w;	clipRect.h = h;
}
void Sprite::Update(float dt){
	if(secondsToSelfDestruct > 0){
		selfDestructCount.Update(dt);
		if(selfDestructCount.Get() > secondsToSelfDestruct) associated.RequestDelete();
	}
	if ((timeElapsed += dt) >= frameTime){
		if(++currentFrame >= frameCount) currentFrame = 0;
		SetFrame(currentFrame);
		timeElapsed = 0;
	}
}
void Sprite::SetFrame(int frame){
	currentFrame = frame;
	int x = frame*GetWidth();
	SetClip(x, clipRect.y, clipRect.w, clipRect.h);
}
void Sprite::SetFrameCount(int frameCount){
	this->frameCount = frameCount;
	currentFrame = 0;
	associated.box.w = GetWidth();
	SetClip(0, clipRect.y, GetWidth(), clipRect.h);
}
void Sprite::Render(){ Render(associated.box.x, associated.box.y); }
void Sprite::Render(float x, float y){
	// TRACE("Sprite::Render");
	SDL_Rect r;
	float auxX = associated.box.w, auxY = associated.box.h;
	r.w = clipRect.w * scale.x; r.h = clipRect.h * scale.y;
	r.x = x - Camera::pos.x; r.y = y - Camera::pos.y;
	// r.x -= r.x - auxX;
	// r.y -= r.y - auxY;
	SDL_RendererFlip flippo = (flip?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), 
		texture.get(), &clipRect, &r,
		angleDeg, nullptr, flippo);
}
void Sprite::SetScaleX(float scaleX, float scaleY){
	if(scaleX != 0) scale.x = scaleX;
	if(scaleY != 0) scale.y = scaleY;
}
void Sprite::SetFrameTime(float frameTime){ this->frameTime = frameTime; }
int Sprite::GetWidth(){ return (width*scale.x)/frameCount; }
int Sprite::GetHeight(){ return height*scale.y; }
bool Sprite::GetFlip(){ return flip;}
void Sprite::SetFlip(bool flip){this->flip = flip;}
Vec2 Sprite::GetScale(){ return scale; }
bool Sprite::IsOpen(){ return (texture != nullptr); }
bool Sprite::Is(std::string type){ return type=="Sprite"; }
Sprite::~Sprite(){ /*TRACE("Sprite::Destrutor");*/ }
