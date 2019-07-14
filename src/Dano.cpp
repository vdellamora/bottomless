#include "../include/Dano.h"
#include "../include/Event.h"
#include "../include/Cecilia.h"

Dano::Dano(Event& associated, int quantidade) : Action(associated){
	this->quantidade = quantidade;
}
Dano::~Dano(){}
void Dano::Execute(){
    Sprite* s = (Sprite*) associated.GetAssociated().GetComponent("Sprite");
    if (s){
        started = true;
        s->SetLoops(false);
        s->NewSprite("assets/img/caranguejaoGolpe.png",19, 0.1f);
        done = true;
        Cecilia::player->InfligirDano(quantidade);
    } else {
        started = true;
        done = true;
    }
}
bool Dano::Is(std::string type){return type == "Dano";}
