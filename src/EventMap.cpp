#include "../include/EventMap.h"
#include "../include/GameObject.h"
#include "../include/Event.h"

EventMap::EventMap(GameObject& associated, int width, int height) : Component(associated){
	this->mapWidth = width;
	this->mapHeight = height;
}
Event EventMap::At(int x, int y){
	//if(x>eventMatrix.size() || y>eventMatrix[x].size()) return 0;
	//return eventMatrix[conta]; 
	for(int i = 0; i<eventMatrix.size(); i++){
		if((eventMatrix[i].GetGrid().x == x) && (eventMatrix[i].GetGrid().y == y)) return eventMatrix[i];
	}
	return Event(associated);
}
void EventMap::AddEvent(int x, int y, int type, bool solido){
	GameObject* ev = new GameObject();
	Event e1 = Event(*ev, type, solido);
	e1.SetGrid(x,y);
	// if(x>eventMatrix.size() || y>eventMatrix[x].size()){ TRACE("Deu ruim aqui, meu bom. Tentou botar evento onde num tem."); return; }
	eventMatrix.push_back(e1);
}
void EventMap::RemoveEvent(Event e){
	// for(int i = 0; i<eventMatrix.size(); i++){
	// 	if(eventMatrix[i] == e){ TRACE("Encontrei o evento pra remocao, e agora?"); return; }
	// }
}

int EventMap::GetWidth(){ return mapWidth;}
int EventMap::GetHeight(){ return mapHeight;}
void EventMap::SetWidth(int width){this->mapWidth = width;}
void EventMap::SetHeight(int height){this->mapHeight = height;}

bool EventMap::Is(std::string type){ return (type == "EventMap");}
void EventMap::Render(){}
EventMap::~EventMap(){}
