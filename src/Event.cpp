#include "../include/Event.h"
#include "../include/Game.h"
#include "../include/State.h"
#include "../include/TestState.h"
#include "../include/Camera.h"
#include "../include/InputManager.h"
#include "../include/Collider.h"
#include "../include/CollisionMap.h"
#include "../include/Sound.h"

Event::Event(GameObject& associated):Component(associated){vazio = true;}
Event::Event(GameObject& associated, int type, bool solido) : Component(associated){
	andando = false;	parou = true;
	direcao = 0;		caminho = 0;
	vazio = false;
	this->type = (type==1?PRESS:TOUCH);
	this->solido = solido;
	associated.AddComponent(new Collider(associated));
}
Event::Event(GameObject& associated, int type, bool solido, std::string file) : Component(associated){
	andando = false;	parou = true;
	direcao = 0;		caminho = 0;
	vazio = false;
	this->type = (type==1?PRESS:TOUCH);
	this->solido = solido;
	spr = new Sprite(associated, file.c_str());
	associated.AddComponent(spr);
	associated.AddComponent(new Collider(associated));
}

void Event::Execute(){
	TRACE("Parece que funcionou o execute");
	//MessageBox mb = MessageBox();
	//mb.Show("Bondia, Cecília.");
}

void Event::SetGrid(int x, int y){
	grid = Vec2(x,y);
	associated.box.x = 64*x;// - associated.box.w/4;
	associated.box.y = 64*y;// - associated.box.h/2;
}

Vec2 Event::GetGrid(){ return grid; }
bool Event::GetSolido(){ return solido; }
int Event::GetType(){ return (this->type==PRESS?1:2); }
bool Event::Is(std::string type){ return type == "Event"; }
Event::~Event(){}
void Event::Start(){}
void Event::Update(float dt){}
void Event::Render(){}
void Event::NotifyCollision(GameObject& other){}