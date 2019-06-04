#include "../include/Camera.h"
#include "../include/InputManager.h"

Vec2 Camera::pos = *new Vec2();
Vec2 Camera::speed = *new Vec2();
GameObject *Camera::focus = nullptr;

void Camera::Update(float dt){
	// TRACE("CameraUpdate");
	if(focus != nullptr){
		if(focus->IsDead()){ Unfollow(); }
		else {
			pos.x = focus->box.x - 1280/2;
			pos.y = focus->box.y - 720/2;
		}
	} else {
		speed.x = 100 * dt;
		speed.y = 100 * dt;

		InputManager im = InputManager::GetInstance();

		// if(im.IsKeyDown(UP_ARROW_KEY)){
		// 	pos.y -= speed.y;
		// }
		// if(im.IsKeyDown(DOWN_ARROW_KEY)){
		// 	pos.y += speed.y;
		// }
		// if(im.IsKeyDown(LEFT_ARROW_KEY)){
		// 	pos.x -= speed.x;
		// }
		// if(im.IsKeyDown(RIGHT_ARROW_KEY)){
		// 	pos.x += speed.x;
		// }
	}
}

void Camera::Follow(GameObject* newFocus){ focus = newFocus; }
void Camera::Unfollow(){ focus = nullptr; }