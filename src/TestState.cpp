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
#include "../include/Sprite.h"
#include "../include/Camera.h"
#include "../include/CameraFollower.h"
#include "../include/Cecilia.h"
#include <cstdlib>
#include <ctime>


TestState::TestState() : State(){
	started = false;

	bg = new GameObject();
	bg->AddComponent(new Sprite(*bg, "assets/img/oceanfloor.jpg"));
	bg->AddComponent(new CameraFollower(*bg));
	objectArray.emplace_back(bg);

	ts = new TileSet(64, 64, "assets/img/TileSubmarino.png");
	tm = new GameObject();
	tm->box.x = 0;
	tm->box.y = 0;
	tm->AddComponent(new TileMap(*tm, 
		"assets/map/tileMap.txt", 
		ts));
	objectArray.emplace_back(tm);

	cm = new GameObject();
	CollisionMap* cmap = new CollisionMap(*cm, 
		"assets/map/tileMap_col.txt");
	cm->AddComponent(cmap);
	objectArray.emplace_back(cm);

	em = new GameObject();
	EventMap* emap = new EventMap(*em, 
		cmap->GetWidth(), cmap->GetHeight());
	em->AddComponent(emap);
	emap->AddEvent("teste1",5,5,1,true); emap->AddEvent("teste2",6,5,1,true);
	emap->AddEvent("testeMove",6,6,0,true,6);
	emap->GetEvent("testeMove")->NewAction(new Move(*(emap->GetEvent("testeMove")), 0, 4));

	crab = new GameObject();
	emap->AddEvent("Caranguejo",8,6,0,true,7);
	emap->AddEvent("CaranguejoOuvido",8,6,2,false);
	emap->GetEvent("Caranguejo")->NewAction(new Dano(*(emap->GetEvent("Caranguejo")), 34));
	emap->GetEvent("CaranguejoOuvido")->SetSomPedido(1);
	emap->GetEvent("CaranguejoOuvido")->NewAction(new Empurravel(*(emap->GetEvent("CaranguejoOuvido"))));

	objectArray.emplace_back(em);

	cecilia = new GameObject();
	Cecilia* comp_c = new Cecilia(*cecilia);
	cecilia->AddComponent(comp_c);
	comp_c->SetGrid(1,7);
	// cecilia->box.x = 512;
	// cecilia->box.y = 512;
	// Camera::Follow(cecilia);
	objectArray.emplace_back(cecilia);

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
	music.Open("assets/audio/fundo.mp3");
	music.Play();
}
void TestState::Update(float dt){
	// TRACE("TestStateUpdate");
	InputManager im = InputManager::GetInstance();
	Camera::Update(dt);

	if(im.QuitRequested()) quitRequested = true;
	if(im.KeyPress(ESCAPE_KEY)){ TRACE("stage POP"); popRequested = true; return;}

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
	bg->GetComponent("Sprite")->Render();
	for(int i = 0; i < objectArray.size(); i++){
		// TRACE("render: " + i);
		objectArray[i].get()->Render();
	}
	// TileMap* topo = (TileMap *) tm->GetComponent("TileMap");
	// topo->Render(1);
}
TileSet& TestState::GetTileSet(){return *ts;}
GameObject& TestState::GetCollisionMap(){return *cm;}
GameObject& TestState::GetEventMap(){return *em;}
TestState::~TestState(){objectArray.clear();}
void TestState::Pause(){}
void TestState::Resume(){}