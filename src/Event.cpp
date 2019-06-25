#include "../include/Event.h"
#include "../include/Game.h"
#include "../include/State.h"
#include "../include/TestState.h"
#include "../include/Camera.h"
#include "../include/InputManager.h"
#include "../include/Collider.h"
#include "../include/CollisionMap.h"
#include "../include/TileSet.h"
#include "../include/Sound.h"

Event::Event(GameObject& associated):Component(associated){vazio = true;}
Event::Event(GameObject& associated, std::string identifier, int type, bool solido) : Component(associated){
	andando = false;	parou = true;
	direcao = 0;		caminho = 0;
	vazio = false;		velocidade = 0;
	tileNumber = -1; this->identifier = identifier;
	this->type = (type==1?PRESS:TOUCH);
	this->solido = solido;
	associated.AddComponent(new Collider(associated));
}
Event::Event(GameObject& associated, std::string identifier, int type, bool solido, std::string file) : Component(associated){
	andando = false;	parou = true;
	direcao = 0;		caminho = 0;
	vazio = false;		velocidade = 0;
	tileNumber = -1; this->identifier = identifier;
	this->type = (type==1?PRESS:TOUCH);
	this->solido = solido;
	spr = new Sprite(associated, file.c_str());
	associated.AddComponent(spr);
	associated.AddComponent(new Collider(associated));
}
Event::Event(GameObject& associated, std::string identifier, int type, bool solido, int tileN) : Component(associated){
	andando = false;	parou = true;
	direcao = 0;		caminho = 0;
	vazio = false;		velocidade = 0;
	tileNumber = -1; this->identifier = identifier;
	this->type = (type==1?PRESS:TOUCH);
	this->solido = solido;
	this->tileNumber = tileN;
	// spr = new Sprite(associated, file.c_str());
	// associated.AddComponent(spr);
	// associated.AddComponent(new Collider(associated));
}
void Event::NewAction(Action* a){
	listaAcoes.push_back(a);
}
void Event::Execute(){
	for(auto i = listaAcoes.begin(); i != listaAcoes.end(); i++){
		(*i)->Execute();
	}
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
int Event::GetType(){ return (this->type==PRESS?1:0); }
std::string Event::GetIdentifier(){ return identifier; }
bool Event::Is(std::string type){ return type == "Event"; }
Event::~Event(){}
void Event::Start(){}
void Event::Update(float dt){
	if(andando){
		grid = Vec2(nx, ny);
		if(caminho<64){
			switch(direcao){
				case 1:
					associated.box.y -= velocidade;
					break;
				case 2:
					associated.box.x += velocidade;
					break;
				case 3:
					associated.box.y += velocidade;
					break;
				case 4:
					associated.box.x -= velocidade;
					break;
			}
			caminho+=velocidade;
			// dbg_tempoWalk += dt;
		} else {
			// TRACE("dbg_tempoWalk: " + TST(dbg_tempoWalk));
			SetGrid(nx,ny);
			andando = false;
			parou = true;
		}
	}
}
void Event::Move(int direcao, int velocidade){
	this->velocidade = velocidade;
	int queroX, queroY; std::string spriteNovo; bool flipa;
	if(direcao == 1){ queroX = grid.x;   queroY = grid.y-1; spriteNovo = ""; flipa = false;}
	if(direcao == 2){ queroX = grid.x+1; queroY = grid.y;   spriteNovo = ""; flipa = false;}
	if(direcao == 3){ queroX = grid.x;   queroY = grid.y+1; spriteNovo = ""; flipa = true;}
	if(direcao == 4){ queroX = grid.x-1; queroY = grid.y;   spriteNovo = ""; flipa = false;}

	if(!VaiColidir(queroX, queroY)){
		//if((this->direcao != direcao) || parou) spr->NewSprite(spriteNovo, 12, CECILIA_ANIMATION_SPEED);
		this->direcao = direcao;
		// spr->SetFlip(flipa);
		andando = true; parou = false;
		caminho = 0; //dbg_tempoWalk = 0;
		nx = queroX; ny = queroY;
	} else {
		this->direcao = direcao; parou = true;
		// spr->NewSprite("assets/img/CeciliaIdle.png", 11, CECILIA_IDLE_SPEED);
		// spr->SetFlip(false);
	}
}
void Event::Ouvir(int som){

}
bool Event::VaiColidir(int x, int y){
	TestState tstate = (TestState&) Game::GetInstance().GetCurrentState();
	CollisionMap* cm = (CollisionMap*) tstate.GetCollisionMap().GetComponent("CollisionMap");
	return cm->At(x,y,0) || cm->At(x,y,1) == 1;
}
void Event::Render(){
	if(tileNumber>=0){
		TestState tstate = (TestState&) Game::GetInstance().GetCurrentState();
		TileSet ts = tstate.GetTileSet();
		ts.RenderTile(tileNumber, associated.box.x, associated.box.y);
	}
}
void Event::NotifyCollision(GameObject& other){}