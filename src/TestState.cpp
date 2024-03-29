#include "../include/TestState.h"
#include "../include/Game.h"
#include "../include/InputManager.h"
#include "../include/GameData.h"
#include "../include/Collision.h"
#include "../include/Collider.h"
#include "../include/TileSet.h"
#include "../include/TileMap.h"
#include "../include/CollisionMap.h"
#include "../include/EventMap.h"
#include "../include/Event.h"
#include "../include/Move.h"
#include "../include/Dano.h"
#include "../include/Empurravel.h"
#include "../include/SaiDoCaminho.h"
#include "../include/Som.h"
#include "../include/Wait.h"
#include "../include/Alavanca.h"
#include "../include/GSwitch.h"
#include "../include/Sprite.h"
#include "../include/Camera.h"
#include "../include/CameraFollower.h"
#include "../include/Cecilia.h"
#include "../include/RevertCarang.h"
#include <cstdlib>
#include <ctime>


TestState::TestState() : State(){
	started = false;

	GameObject* bg = new GameObject();
  	bg->AddComponent(new Sprite(*bg, "assets/img/oceanfloor.jpg"));
  	bg->AddComponent(new CameraFollower(*bg));
  	objectArray.emplace_back(bg);

	ts = new TileSet(64, 64, "assets/img/TileSubmarino.png");
	// ts = new TileSet(96, 96, "assets/img/oceanTileSet.png");
	tm = new GameObject();
	tm->box.x = 0;
	tm->box.y = 0;
	tm->AddComponent(new TileMap(*tm, "assets/map/ocean_Map.txt", ts));
	// tm->AddComponent(new TileMap(*tm, "assets/map/ocean1_Map.txt", ts));
	objectArray.emplace_back(tm);

	cm = new GameObject();
	CollisionMap* cmap = new CollisionMap(*cm, "assets/map/ocean_Col.txt");
	// CollisionMap* cmap = new CollisionMap(*cm, "assets/map/ocean1_Col.txt");
	cm->AddComponent(cmap);
	objectArray.emplace_back(cm);
	
	music = Music();
	quitRequested = false;
}

void TestState::Start(){
	if(popRequested) return;
	StartArray();
	LoadAssets();
}

void TestState::LoadAssets(){
	// Carregar tudo
	em = new GameObject();
	CollisionMap* cmap = (CollisionMap*) cm->GetComponent("CollisionMap");

	EventMap* emap = new EventMap(*em, 
		cmap->GetWidth(), cmap->GetHeight());
	em->AddComponent(emap);
//  emap->AddEvent("teste1",5,5,1,true); emap->AddEvent("teste2",6,5,1,true);
//  emap->AddEvent("testeMove",6,6,0,true,6);
//  emap->GetEvent("testeMove")->NewAction(new Move(*(emap->GetEvent("testeMove")), 0, 4));

	crab = new GameObject();
	emap->AddEvent("Caranguejo",8,6,0,true,"assets/img/caranguejao.png",20);
	emap->AddEvent("CaranguejoOuvido",8,6,2,false);
	emap->GetEvent("Caranguejo")->NewAction(new Dano(*(emap->GetEvent("Caranguejo")), 34));
	emap->GetEvent("CaranguejoOuvido")->SetSomPedido(1);
	emap->GetEvent("CaranguejoOuvido")->NewAction(new Empurravel(*(emap->GetEvent("CaranguejoOuvido"))));
    emap->GetEvent("Caranguejo")->NewAction(new RevertCarang(*(emap->GetEvent("Caranguejo"))));

  emap->AddEvent("corneta1",13,5,-1,true,31);
  emap->GetEvent("corneta1")->NewAction(new Som(*(emap->GetEvent("corneta1")), 2));

  emap->AddEvent("corneta2",15,5,-1,true,31);
  emap->GetEvent("corneta2")->NewAction(new Wait(*(emap->GetEvent("corneta2")), 2));
  emap->GetEvent("corneta2")->NewAction(new Som(*(emap->GetEvent("corneta2")), 3));

  emap->AddEvent("corneta3",17,5,-1,true,30);
  emap->GetEvent("corneta3")->NewAction(new Wait(*(emap->GetEvent("corneta3")), 4));
  emap->GetEvent("corneta3")->NewAction(new GSwitch(*(emap->GetEvent("corneta3")), 0, true));
  emap->GetEvent("corneta3")->NewAction(new Som(*(emap->GetEvent("corneta3")), 5));
  emap->GetEvent("corneta3")->NewAction(new Wait(*(emap->GetEvent("corneta3")), 1));
  emap->GetEvent("corneta3")->NewAction(new GSwitch(*(emap->GetEvent("corneta3")), 0, false));

	emap->AddEvent("alavanca",11,4,1,true,23);
	emap->GetEvent("alavanca")->NewAction(new Alavanca(*(emap->GetEvent("alavanca"))));

	emap->AddEvent("AguaViva",18,6,2,true, "assets/img/aguaviva.png",10);
  	emap->GetEvent("AguaViva")->SetSomPedido(4);
 	emap->GetEvent("AguaViva")->NewAction(new SaiDoCaminho(*(emap->GetEvent("AguaViva"))));

	objectArray.emplace_back(em);

	cecilia = new GameObject();
	Cecilia* comp_c = new Cecilia(*cecilia);
	cecilia->AddComponent(comp_c);
	comp_c->SetGrid(1,7);
	// Camera::Follow(cecilia);
	objectArray.emplace_back(cecilia);

	music.Open("assets/audio/fundo.ogg");
	music.Play();
}
void TestState::Update(float dt){
	InputManager im = InputManager::GetInstance();
	Camera::Update(dt);

	if(im.QuitRequested()) quitRequested = true;
	if(im.KeyPress(ESCAPE_KEY)){ TRACE("stage POP"); popRequested = true; return;}

	EventMap* emap = (EventMap*) em->GetComponent("EventMap");
	if(emap->GetEvent("Caranguejo") != nullptr){
		if((emap->GetEvent("Caranguejo")->GetGrid().x == 10) && (emap->GetEvent("Caranguejo")->GetParouMovimento())){
			
			emap->GetEvent("Caranguejo")->ClearActions();
			emap->GetEvent("Caranguejo")->SetSolido(false);
			TRACE("ALTERA CARANGUEJO");
			((CollisionMap*) cm->GetComponent("CollisionMap"))->AlteraTile(
      		emap->GetEvent("Caranguejo")->GetGrid().x,
      		emap->GetEvent("Caranguejo")->GetGrid().y, 0, 0);	// Altera a colisão do chão
			TRACE("ALTERA COLISAO");
			
			// TRACE(TST(((CollisionMap*) cm->GetComponent("CollisionMap"))->At(
   //    		emap->GetEvent("Caranguejo")->GetGrid().x,
   //    		emap->GetEvent("Caranguejo")->GetGrid().y, 0)));
			emap->GetEvent("Caranguejo")->SetIdentifier("CaranguejoDormindo");
			TRACE("FINALIZA CARANGUEJO");


			emap->AddEvent("Golfinho1",11,9,1,true,"assets/img/arenque1.png",13);
			emap->GetEvent("Golfinho1")->NewAction(new Som(*(emap->GetEvent("Golfinho1")), 2));
			emap->AddEvent("Golfinho2",13,8,1,true,"assets/img/arenque1.png",13);
			emap->GetEvent("Golfinho2")->NewAction(new Som(*(emap->GetEvent("Golfinho2")), 3));
			emap->AddEvent("Golfinho3",15,9,1,true,"assets/img/arenque1.png",13);
			emap->GetEvent("Golfinho3")->NewAction(new Som(*(emap->GetEvent("Golfinho3")), 4));
			TRACE("ADICIONA GOLFINHOS");

	      emap->GetEvent("Golfinho1")->Execute();
	      emap->GetEvent("Golfinho2")->Execute();
	      emap->GetEvent("Golfinho3")->Execute();
		}
	}


	for(int i = 0; i < objectArray.size(); i++){
		objectArray[i].get()->Update(dt);

		Collider* col1 = (Collider *) objectArray[i]->GetComponent("Collider");
		if(col1){
			for(int j = i+1; j < objectArray.size(); j++){
				Collider* col2 = (Collider *) objectArray[j]->GetComponent("Collider");
				if(col2){
					Sprite* spr1 = (Sprite*) objectArray[i]->GetComponent("Sprite");
					Sprite* spr2 = (Sprite*) objectArray[j]->GetComponent("Sprite");
					//spr->angleDeg -= 0.3f;
					if(Collision::IsColliding(
						col1->box, col2->box, 
						spr1->angleDeg, spr2->angleDeg)){
						objectArray[i]->NotifyCollision(*objectArray[j]);
						objectArray[j]->NotifyCollision(*objectArray[i]);
					}
				}
			}
		}

		if(objectArray[i]->IsDead()) {
			/*Sound* s = (Sound *) objectArray[i]->GetComponent("Sound");
			if (((s) && (!(s->IsPlaying()))) || (!s)){ if(s)TRACE("Tem som");*/
			objectArray.erase(objectArray.begin()+i);//}
		}
	}

}
void TestState::Render(){
	for(int i = 0; i < objectArray.size(); i++){
		// TRACE("render: " + i);
		objectArray[i].get()->Render();
	}
	// TileMap* topo = (TileMap *) tm->GetComponent("TileMap");
	// topo->Render(1);
}
TestState::~TestState(){objectArray.clear();}
void TestState::Pause(){}
void TestState::Resume(){}
