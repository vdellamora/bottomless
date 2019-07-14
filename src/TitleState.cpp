//
//  TitleState.cpp
//  IDJ_2018
//
//  Created by Thiago Dantas on 26/06/19.
//  Copyright © 2019 Thiago Dantas. All rights reserved.
//

#include <stdio.h>
#include "../include/TitleState.h"
#include "../include/TestState.h"
#include "../include/Game.h"
#include "../include/InputManager.h"
#include "../include/GameData.h"
//#include "../include/Collision.h"
//#include "../include/Collider.h"
#include "../include/TileSet.h"
#include "../include/TileMap.h"
#include "../include/CollisionMap.h"
//#include "../include/EventMap.h"
//#include "../include/Event.h"
//#include "../include/Move.h"
#include "../include/Sprite.h"
#include "../include/Camera.h"
#include "../include/CameraFollower.h"
#include "../include/Text.h"

TitleState::TitleState(){
  started = false;
  
  LoadAssets();
}
TitleState::~TitleState(){
  
}
void TitleState::LoadAssets(){
  bg = new GameObject();
  objectArray.emplace_back(bg);
  bg->AddComponent(new Sprite(*bg, "assets/img/chtullu.png"));
  bg->AddComponent(new CameraFollower(*bg));
  SDL_Color textcolor = {0,0,0,255};
  GameObject* start = new GameObject();
  start->AddComponent(new Text(*start, "assets/font/Call me maybe.ttf", 50, Text::TextStyle::SOLID, "Start", textcolor));
  
  start->box.x = 120;
  start->box.y = 140;
  buttons.push_back(Rect(110,130,200,100));
  AddObject(start);
  
  GameObject* options = new GameObject();
  options->AddComponent(new Text(*options, "assets/font/Call me maybe.ttf", 50, Text::TextStyle::SOLID, "Options", textcolor));
  options->box.x = 120;
  options->box.y = 230;
  buttons.push_back(Rect(110,220,200,100));
  AddObject(options);
  
  GameObject* exit = new GameObject();
  exit->AddComponent(new Text(*exit, "assets/font/Call me maybe.ttf", 50, Text::TextStyle::SOLID, "Exit", textcolor));
  exit->box.x = 120;
  exit->box.y = 320;
  buttons.push_back(Rect(110,310,200,100));
  AddObject(exit);
  
}
void TitleState::Update(float dt){
  InputManager im = InputManager::GetInstance();
  Camera::Update(dt);
  
  if(im.QuitRequested()) quitRequested = true;
  if(im.KeyPress(ESCAPE_KEY)){ TRACE("stage POP"); popRequested = true; return;}
  if(im.MousePress(LEFT_MOUSE_BUTTON)){
    Vec2 mouse = Vec2(im.GetMouseX(), im.GetMouseY());
    for (int i  = 0; i < buttons.size(); i++){
      if (buttons[i].IsInside(&mouse)){
        switch (i) {
          case 0:
            printf("start");
                Game::GetInstance().Push(new TestState());
            // push game state;
            break;
          case 1:
            printf("options");
                
            // present options
            break;
          case 2:
            printf("Exit\n");
            popRequested = true;
          default:
            break;
        }
      }
    }
  }
  
  
}
void TitleState::Render(){
//  bg->GetComponent("Sprite")->Render();
  for(int i = 0; i < objectArray.size(); i++){
    // TRACE("render: " + i);
    objectArray[i].get()->Render();
  }
}
void TitleState::Start(){
  started = true;
}
void TitleState::Pause(){
  
}
void TitleState::Resume(){
  
}

TileSet& TitleState::GetTileSet(){
  return *ts;
}
