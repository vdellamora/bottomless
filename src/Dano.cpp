#include "../include/Dano.h"
#include "../include/Event.h"
#include "../include/Cecilia.h"

Dano::Dano(Event& associated, int quantidade) : Action(associated){
	this->quantidade = quantidade;
}
Dano::~Dano(){}
void Dano::Execute(){
	// Event* e = (Event*) associated.GetComponent("Event");
	Cecilia::player->InfligirDano(quantidade);
	done = true;
}
bool Dano::Is(std::string type){return type == "Dano";}
