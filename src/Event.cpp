#include "../include/Event.h"
#include "../include/Game.h"
#include "../include/State.h"
#include "../include/Camera.h"
#include "../include/InputManager.h"
#include "../include/Collider.h"
#include "../include/CollisionMap.h"
#include "../include/TileSet.h"
#include "../include/Sound.h"

Event::Event(GameObject& associated):Component(associated){
  vazio = true;
  next = nullptr;
}
Event::Event(GameObject& associated, std::string identifier, int type, bool solido) : Component(associated){
	andando = false;	parou = true;
	direcao = 0;		caminho = 0;
	vazio = false;		velocidade = 0;
	somPedido = 0;		spr = nullptr;
  executando = false;
	tileNumber = -1; this->identifier = identifier;
	this->type = type;
	this->solido = solido;
	associated.AddComponent(new Collider(associated));
  next = nullptr;
}
Event::Event(GameObject& associated, std::string identifier, int type, bool solido, std::string file, int frames) : Component(associated){
	andando = false;	parou = true;
	direcao = 0;		caminho = 0;
	vazio = false;		velocidade = 0;
	somPedido = 0;
  executando = false;
	tileNumber = -1; this->identifier = identifier;
	this->type = type;
	this->solido = solido;
	spr = new Sprite(associated, file.c_str(), frames, EVENT_IDLE_SPEED);
	associated.AddComponent(spr);
	associated.AddComponent(new Collider(associated));
  next = nullptr;
}
Event::Event(GameObject& associated, std::string identifier, int type, bool solido, int tileN) : Component(associated){
	andando = false;	parou = true;
	direcao = 0;		caminho = 0;
	vazio = false;		velocidade = 0;
	somPedido = 0;		spr = nullptr;
  executando = false;
	tileNumber = -1; this->identifier = identifier;
	this->type = type;
	this->solido = solido;
	this->tileNumber = tileN;
	// spr = new Sprite(associated, file.c_str());
	// associated.AddComponent(spr);
	// associated.AddComponent(new Collider(associated));
  next = nullptr;
}
void Event::NewAction(Action* a){
	listaAcoes.push_back(a);
}
bool Event::GetExecutando(){return executando;}
void Event::Execute(){
	eventoAtual = 0;
	executando = true;
  TRACE(this->identifier);
  
}
void Event::SetNext(Event* n){
  this->next = n;
}
void Event::Execute(int som){
	TRACEN("som pedido: "); TRACE(TST(somPedido));
	if(som != somPedido) return;
	for(auto i = listaAcoes.begin(); i != listaAcoes.end(); i++){
		(*i)->Execute();
	}
}
void Event::SetSomPedido(int som){somPedido = som;}
int Event::GetSomPedido(){return somPedido;}

void Event::SetGrid(int x, int y){
	grid = Vec2(x,y);
	float ajustex = 0;
	float ajustey = 0;
	if(spr != nullptr){
		ajustex = associated.box.w/4;
		ajustey = associated.box.h/2;
	}

	associated.box.x = 64*x - ajustex;// - associated.box.w/4;
	associated.box.y = 64*y - ajustey;// - associated.box.h/2;
}
bool Event::GetParouMovimento(){return (!andando && parou);}
Vec2 Event::GetGrid(){ return grid; }
bool Event::GetSolido(){ return solido; }
int Event::GetType(){ return this->type; }
std::string Event::GetIdentifier(){ return identifier; }
bool Event::Is(std::string type){ return type == "Event"; }
Event::~Event(){listaAcoes.clear();}
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

	if(executando){
    TRACEN("executando ");
    TRACE(identifier);
    
		if(eventoAtual < listaAcoes.size()){
			
			if(listaAcoes[eventoAtual]->GetStarted()){
				if((listaAcoes[eventoAtual])->GetDone()){
				eventoAtual++;
				} else {
					(listaAcoes[eventoAtual])->Update(dt);
				}
			} else {
				(listaAcoes[eventoAtual])->Execute();
			}
			
		} else {
			executando = false;
      if (identifier == "corneta1"){
        TRACE(SDL_GetTicks());
      }
      if (identifier == "corneta2"){
        TRACE(SDL_GetTicks());
        TRACE("Gambirra");
      }
      for (auto a:listaAcoes) a->Reset();
      if (next != nullptr ) next->Execute();
      TRACEN("Executou ");
      TRACE(identifier);
      
    }
	}

	if(spr != nullptr) spr->Update(dt);
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
bool Event::VaiColidir(int x, int y){
	State tstate = Game::GetInstance().GetCurrentState();
	CollisionMap* cm = (CollisionMap*) tstate.GetCollisionMap().GetComponent("CollisionMap");
	return cm->At(x,y,0) == 1 || cm->At(x,y,1) == 1;
}
void Event::Render(){
	if(tileNumber>=0){
		State tstate = Game::GetInstance().GetCurrentState();
		TileSet ts = tstate.GetTileSet();
		ts.RenderTile(tileNumber, associated.box.x, associated.box.y);
	}

	if(spr != nullptr) spr->Render();
}
void Event::NotifyCollision(GameObject& other){}
GameObject& Event::GetAssociated(){return associated;}
