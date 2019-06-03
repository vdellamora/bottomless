#include "../include/GameObject.h"

GameObject::GameObject(){
	started = false;
	isDead = false;
	box.x = 0;
	box.y = 0;
	box.w = 0;
	box.h = 0;
	// std::cout << "Construtor do GameObject" << std::endl;
}
GameObject::~GameObject(){
	// std::cout << "Destrutor do GameObject" << std::endl;
	// for(int i = components.size(); i>=0; i--){
	// 	delete components[i];
	// }
	components.clear();
}

void GameObject::Start(){
	for(int i = 0; i<components.size(); i++){
		components[i].get()->Start();
	}
	started = true;
}

void GameObject::Update(float dt){
	for(int i = 0; i<components.size(); i++){
		components[i].get()->Update(dt);
	}
}
void GameObject::Render(){
	// std::cout << "Render do GameObject" << std::endl;
	for(int i = 0; i<components.size(); i++){
		components[i].get()->Render();
	}
}
void GameObject::NotifyCollision(GameObject& other){
	for(int i = 0; i<components.size(); i++){
		components[i].get()->NotifyCollision(other);
	}
}
bool GameObject::IsDead(){return isDead;}
void GameObject::RequestDelete(){isDead = true;}
void GameObject::AddComponent(Component* c){
	// std::cout << "AddCpt do GO" << std::endl;
	components.emplace_back(c);
}
void GameObject::RemoveComponent(Component* c){
	for(int i = 0; i<components.size(); i++){
		if(components[i].get() == c) components.erase(components.begin()+i);
	}
}
Component* GameObject::GetComponent(std::string type){
	for(auto i = components.begin(); i != components.end(); i++){
		if((*i)->Is(type)) return (*i).get();
	}
	// for(int i = 0; i<components.size(); i++){
	// 	if(components[i]->Is(type)) return components[i];
	// }
	return nullptr;
}