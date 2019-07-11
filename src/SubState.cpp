#include "../include/SubState.h"
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
#include "../include/Som.h"
#include "../include/Wait.h"
#include "../include/Alavanca.h"
#include "../include/GSwitch.h"
#include "../include/Sprite.h"
#include "../include/Camera.h"
#include "../include/CameraFollower.h"
#include "../include/Cecilia.h"
#include <cstdlib>
#include <ctime>


SubState::SubState() : State(){
	started = false;

	GameObject* bg = new GameObject();
  bg->AddComponent(new Sprite(*bg, "assets/img/preto_script.png"));
  bg->AddComponent(new CameraFollower(*bg));
  GameObject* bg2 = new GameObject();
  bg2->AddComponent(new Sprite(*bg2, "assets/img/cockpit.png"));
  
	objectArray.emplace_back(bg);
  objectArray.emplace_back(bg2);

	cm = new GameObject();
	CollisionMap* cmap = new CollisionMap(*cm, "assets/map/cockpit.txt");
	cm->AddComponent(cmap);
	objectArray.emplace_back(cm);

	music = Music();
	quitRequested = false;
}

void SubState::Start(){
	if(popRequested) return;
	StartArray();
	LoadAssets();
}

void SubState::LoadAssets(){
	// Carregar tudo
	em = new GameObject();
	CollisionMap* cmap = (CollisionMap*) cm->GetComponent("CollisionMap");

	EventMap* emap = new EventMap(*em, cmap->GetWidth(), cmap->GetHeight());
	em->AddComponent(emap);
	objectArray.emplace_back(em);

	cecilia = new GameObject();
	Cecilia* comp_c = new Cecilia(*cecilia);
	cecilia->AddComponent(comp_c);
	comp_c->SetGrid(8,14);
  Camera::Follow(cecilia);
	objectArray.emplace_back(cecilia);

  // if(!__APPLE__){
  //   music.Open("assets/audio/fundo.mp3");
  //   music.Play();
  // }
}
void SubState::Update(float dt){
	// TRACE("SubStateUpdate");
	InputManager im = InputManager::GetInstance();
	Camera::Update(dt);

	if(im.QuitRequested()) quitRequested = true;
	if(im.KeyPress(ESCAPE_KEY)){ TRACE("stage POP"); popRequested = true; return;}

  EventMap* emap = (EventMap*) em->GetComponent("EventMap");


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
void SubState::Render(){
//  bg->GetComponent("Sprite")->Render();
	for(int i = 0; i < objectArray.size(); i++){
		// TRACE("render: " + i);
		objectArray[i].get()->Render();
	}
	// TileMap* topo = (TileMap *) tm->GetComponent("TileMap");
	// topo->Render(1);
}
SubState::~SubState(){objectArray.clear();}
void SubState::Pause(){}
void SubState::Resume(){}
