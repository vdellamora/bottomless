#include "../include/EventMap.h"
#include "../include/GameObject.h"
#include "../include/Event.h"

EventMap::EventMap(GameObject& associated, int width, int height) : Component(associated){
	this->mapWidth = width;
	this->mapHeight = height;
}
Event* EventMap::At(int x, int y){
	//if(x>eventMatrix.size() || y>eventMatrix[x].size()) return 0;
	//return eventMatrix[conta]; 
	for(auto i = eventMatrix.begin(); i!=eventMatrix.end(); i++){
		if(((*i)->GetGrid().x == x) && ((*i)->GetGrid().y == y)) return (*i);
	}
	return new Event(associated);
}
void EventMap::AddEvent(std::string identifier, int x, int y, int type, bool solido){
	GameObject* ev = new GameObject();
	Event* e1 = new Event(*ev, identifier, type, solido);
	e1->SetGrid(x,y);
	// if(x>eventMatrix.size() || y>eventMatrix[x].size()){ TRACE("Deu ruim aqui, meu bom. Tentou botar evento onde num tem."); return; }
	eventMatrix.push_back(e1);
}
void EventMap::AddEvent(std::string identifier, int x, int y, int type, bool solido, std::string sprite, int frames){
	GameObject* ev = new GameObject();
	Event* e1 = new Event(*ev, identifier, type, solido, sprite, frames);
	e1->SetGrid(x,y);
	eventMatrix.push_back(e1);
}
void EventMap::AddEvent(std::string identifier, int x, int y, int type, bool solido, int tileN){
	GameObject* ev = new GameObject();
	Event* e1 = new Event(*ev, identifier, type, solido, tileN);
	e1->SetGrid(x,y);
	eventMatrix.push_back(e1);
}

Event* EventMap::GetEvent(std::string identifier){
	for(int i = 0; i<eventMatrix.size(); i++){
		if(eventMatrix[i]->GetIdentifier() == identifier){ return eventMatrix[i]; }
	}
  return nullptr;
}
void EventMap::RemoveEvent(std::string evento){
	for(int i = 0; i<eventMatrix.size(); i++){
		if(eventMatrix[i]->GetIdentifier() == evento){ eventMatrix.erase(eventMatrix.begin()+i); return;}
	}
}
void EventMap::OuvirEventos(int som){
	TRACE("Ouvindo eventos");
	for(int i = 0; i<eventMatrix.size(); i++){
		TRACEN("Evento do tipo: "); TRACE(std::to_string(eventMatrix[i]->GetType()));
		if(eventMatrix[i]->GetType()==2){ TRACE("evento vai ouvir"); eventMatrix[i]->Execute(som);}
	}
}
void EventMap::Update(float dt){
	for(int i = 0; i<eventMatrix.size(); i++){
		eventMatrix[i]->Update(dt);
	}
}
void EventMap::Render(){
	for(int i = 0; i<eventMatrix.size(); i++){
		eventMatrix[i]->Render();
	}
}


int EventMap::GetWidth(){ return mapWidth;}
int EventMap::GetHeight(){ return mapHeight;}
void EventMap::SetWidth(int width){this->mapWidth = width;}
void EventMap::SetHeight(int height){this->mapHeight = height;}
bool EventMap::Is(std::string type){ return (type == "EventMap");}
EventMap::~EventMap(){}
