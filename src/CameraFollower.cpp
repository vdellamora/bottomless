#include "../include/CameraFollower.h"
#include "../include/Camera.h"

CameraFollower::CameraFollower(GameObject& associated) : Component(associated){
	TRACE("CameraFollower");
}
CameraFollower::~CameraFollower(){

}

void CameraFollower::Update(float dt){
	associated.box.x = Camera::pos.x;
	associated.box.y = Camera::pos.y;
}

void CameraFollower::Render(){}
bool CameraFollower::Is(std::string type){ return type == "CameraFollower"; }