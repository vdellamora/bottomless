#include "../include/Cecilia.h"
#include "../include/Game.h"
#include "../include/State.h"
#include "../include/TestState.h"
#include "../include/Camera.h"
#include "../include/InputManager.h"
#include "../include/Collider.h"
#include "../include/CollisionMap.h"
#include "../include/EventMap.h"
#include "../include/Event.h"
#include "../include/Sound.h"

Cecilia *Cecilia::player = nullptr;

Cecilia::Cecilia(GameObject& associated) : Component(associated){
	andando = false;	parou = true;
	direcao = 2;		caminho = 0;
	speed = Vec2(0, 0); hp = 100;
	spr = new Sprite(associated, "assets/img/CeciliaIdle.png", 11, CECILIA_IDLE_SPEED);
	spr->SetFlip(true);
	associated.AddComponent(spr);
	associated.AddComponent(new Collider(associated));
	Cecilia::player = this;
}
void Cecilia::Update(float dt){
	InputManager im = InputManager::GetInstance();

	if(im.KeyPress(Z_KEY) && !andando){
		switch(direcao){
			case 1:
				VaiInteragir(grid.x, grid.y-1);
				break;
			case 2:
				VaiInteragir(grid.x+1, grid.y);
				break;
			case 3:
				VaiInteragir(grid.x, grid.y+1);
				break;
			case 4:
				VaiInteragir(grid.x-1, grid.y);
				break;
		}
	}

	if(im.IsKeyDown(UP_ARROW_KEY) && !andando){
		if(!VaiColidir(grid.x,grid.y-1)){
			if((direcao != 1) || parou) spr->NewSprite("assets/img/CeciliaWalkRight.png", 12, CECILIA_ANIMATION_SPEED);
			spr->SetFlip(true);
			direcao = 1;
			andando = true;
			parou = false;
			caminho = 0;
			dbg_tempoWalk = 0;
			nx = grid.x;
			ny = grid.y-1;
		} else {
			direcao = 1;
			parou = true;
			spr->NewSprite("assets/img/CeciliaIdle.png", 11, CECILIA_IDLE_SPEED);
			spr->SetFlip(false);
		}
	}
	if(im.IsKeyDown(RIGHT_ARROW_KEY) && !andando){
		if(!VaiColidir(grid.x+1,grid.y)){
			if((direcao != 2) || parou) spr->NewSprite("assets/img/CeciliaWalkRight.png", 12, CECILIA_ANIMATION_SPEED);
			spr->SetFlip(false);
			direcao = 2;
			andando = true;
			parou = false;
			caminho = 0;
			dbg_tempoWalk = 0;
			nx = grid.x+1;
			ny = grid.y;
		} else {
			direcao = 2;
			parou = true;
			spr->NewSprite("assets/img/CeciliaIdle.png", 11, CECILIA_IDLE_SPEED);
			spr->SetFlip(true);
		}
	}
	if(im.IsKeyDown(DOWN_ARROW_KEY) && !andando){
		if(!VaiColidir(grid.x,grid.y+1)){
			if((direcao != 3) || parou) spr->NewSprite("assets/img/CeciliaWalkRight.png", 12, CECILIA_ANIMATION_SPEED);
			spr->SetFlip(false);
			direcao = 3;
			andando = true;
			parou = false;
			caminho = 0;
			dbg_tempoWalk = 0;
			nx = grid.x;
			ny = grid.y+1;
		} else {
			direcao = 3;
			parou = true;
			spr->NewSprite("assets/img/CeciliaIdle.png", 11, CECILIA_IDLE_SPEED);
			spr->SetFlip(true);
		}
	}
	if(im.IsKeyDown(LEFT_ARROW_KEY) && !andando){
		if(!VaiColidir(grid.x-1,grid.y)){
			if((direcao != 4) || parou) spr->NewSprite("assets/img/CeciliaWalkRight.png", 12, CECILIA_ANIMATION_SPEED);
			spr->SetFlip(true);
			direcao = 4;
			andando = true;
			parou = false;
			caminho = 0;
			dbg_tempoWalk = 0;
			nx = grid.x-1;
			ny = grid.y;
		} else {
			direcao = 4;
			parou = true;
			spr->NewSprite("assets/img/CeciliaIdle.png", 11, CECILIA_IDLE_SPEED);
			spr->SetFlip(false);
		}
	}

	if(andando){
		if(caminho<64){
			switch(direcao){
				case 1:
					associated.box.y -= CECILIA_MOVE_SPEED;
					break;
				case 2:
					associated.box.x += CECILIA_MOVE_SPEED;
					break;
				case 3:
					associated.box.y += CECILIA_MOVE_SPEED;
					break;
				case 4:
					associated.box.x -= CECILIA_MOVE_SPEED;
					break;
			}
			caminho+=CECILIA_MOVE_SPEED;
			dbg_tempoWalk += dt;
		} else {
			TRACE("dbg_tempoWalk: " + TST(dbg_tempoWalk));
			SetGrid(nx,ny);
			andando = false;
			if(!im.IsKeyDown(UP_ARROW_KEY) &&
				!im.IsKeyDown(RIGHT_ARROW_KEY) &&
				!im.IsKeyDown(DOWN_ARROW_KEY) &&
				!im.IsKeyDown(LEFT_ARROW_KEY)){
				parou = true;
				switch(direcao){
					case 1:
						spr->NewSprite("assets/img/CeciliaIdle.png", 11, CECILIA_IDLE_SPEED);
						spr->SetFlip(false);
						break;
					case 2:
						spr->NewSprite("assets/img/CeciliaIdle.png", 11, CECILIA_IDLE_SPEED);
						spr->SetFlip(true);
						break;
					case 3:
						spr->NewSprite("assets/img/CeciliaIdle.png", 11, CECILIA_IDLE_SPEED);
						spr->SetFlip(true);
						break;
					case 4:
						spr->NewSprite("assets/img/CeciliaIdle.png", 11, CECILIA_IDLE_SPEED);
						spr->SetFlip(false);
						break;
				}
			}
		}
	}

	////////////////////////////////////
	if(hp<=0){
		Camera::Unfollow();
		associated.RequestDelete();
	}
}
bool Cecilia::VaiColidir(int x, int y){
	TestState tstate = (TestState&) Game::GetInstance().GetCurrentState();
	CollisionMap* cm = (CollisionMap*) tstate.GetCollisionMap().GetComponent("CollisionMap");
	return cm->At(x,y,0) || cm->At(x,y,1) == 1;
}
void Cecilia::VaiInteragir(int x, int y){
	TestState tstate = (TestState&) Game::GetInstance().GetCurrentState();
	EventMap* em = (EventMap*) tstate.GetEventMap().GetComponent("EventMap");
	Event e = em->At(x,y);
	if(e.vazio) return;
	if(e.GetType()==1) e.Execute();
}
void Cecilia::NotifyCollision(GameObject& other){
	// Bullet* bul = (Bullet*) other.GetComponent("Bullet");
	// if(bul && bul->targetsPlayer) hp -= bul->GetDamage();;
}
void Cecilia::SetGrid(int x, int y){
	grid = Vec2(x,y);
	associated.box.x = 64*x - associated.box.w/4;
	associated.box.y = 64*y - associated.box.h/2;
}
bool Cecilia::Is(std::string type){ return type == "Cecilia"; }
Cecilia::~Cecilia(){player = nullptr;}
void Cecilia::Start(){}
void Cecilia::Render(){}

//////////////////////////////////////// UNUSED
	// if(im.IsKeyDown(RIGHT_ARROW_KEY)) speed.x = 3;
	// if(im.IsKeyDown(LEFT_ARROW_KEY)) speed.x = -3;
	// if(im.IsKeyDown(DOWN_ARROW_KEY)) speed.y = 3;
	// if(im.IsKeyDown(UP_ARROW_KEY)) speed.y = -3;

	// if(!im.IsKeyDown(RIGHT_ARROW_KEY) && !im.IsKeyDown(LEFT_ARROW_KEY)) speed.x = 0;
	// if(!im.IsKeyDown(DOWN_ARROW_KEY) && !im.IsKeyDown(UP_ARROW_KEY)) speed.y = 0;

	// if(!im.IsKeyDown(RIGHT_ARROW_KEY) && !im.IsKeyDown(LEFT_ARROW_KEY) && !im.IsKeyDown(DOWN_ARROW_KEY) && !im.IsKeyDown(UP_ARROW_KEY))
	// 	if((direcao == 2)||(direcao == 4))spr->NewSprite("assets/img/CeciliaIdle.png");

	// associated.box.x += speed.x;
	// associated.box.y += speed.y;




	// Será utilizado depois para uma animação de morte
	// GameObject* explosao = new GameObject();
	// explosao->AddComponent(new Sprite(*explosao, "assets/img/penguindeath.png", 5, 0.1f, 0.5f));
	// explosao->box.x = associated.box.x;
	// explosao->box.y = associated.box.y;
	// Sound* som = new Sound(*explosao, "assets/audio/boom.wav");
	// explosao->AddComponent(som);
	// som->Play();