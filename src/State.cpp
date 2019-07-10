#include "../include/State.h"

State::State(){
	popRequested = false;
	quitRequested = false;
	started = false;
}
State::~State(){
	for(auto i = objectArray.rbegin(); i != objectArray.rend(); ++i) {
        (*i).reset();
    }
	objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go){
	std::shared_ptr<GameObject> sptr(go);
	objectArray.emplace_back(sptr);
	if (started) go->Start();
	std::weak_ptr<GameObject> wptr = sptr;
	return wptr;
}
std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){
	for(int i = 0; i < objectArray.size(); i++){
		if(objectArray[i].get() == go) 
			return std::weak_ptr<GameObject> (objectArray[i]);
	}
	return std::weak_ptr<GameObject>();
}


void State::StartArray(){
	for(int i = 0; i < objectArray.size(); i++){
		// TRACE("render: " + i);
		objectArray[i].get()->Start();
	}
	started = true;
}
void State::UpdateArray(float dt){
	for(int i = 0; i < objectArray.size(); i++){
		objectArray[i].get()->Update(dt);
	}
}
void State::RenderArray(){
	for(int i = 0; i < objectArray.size(); i++){
		// TRACE("render: " + i);
		objectArray[i].get()->Render();
	}
}
void State::LoadAssets(){}
void State::Update(float){}
void State::Render(){}
void State::Start(){}
void State::Resume(){}
void State::Pause(){}
bool State::PopRequested(){ return popRequested;}
bool State::QuitRequested(){ return quitRequested;}
TileSet& State::GetTileSet(){return *ts;}
GameObject& State::GetCollisionMap(){return *cm;}
GameObject& State::GetEventMap(){return *em;}
