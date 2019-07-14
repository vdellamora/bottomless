//
//  TitleState.h
//  IDJ_2018
//
//  Created by Thiago Dantas on 26/06/19.
//  Copyright © 2019 Thiago Dantas. All rights reserved.
//


#ifndef TitleState_h
#define TitleState_h

#include "inclusao.h"
#include "State.h"
#include "GameObject.h"
#include "Music.h"
#include "TileSet.h"
#include <vector>
#include "Rect.h"

class TitleState : public State{
  
public:
  TitleState();
  ~TitleState();
  void LoadAssets();
  void Update(float);
  void Render();
  void Start();
  void Pause();
  void Resume();
  
  TileSet& GetTileSet();
private:
  
  std::vector<Rect> buttons;
  GameObject* bg;
  TileSet* ts;
  Music music;
  
};


#endif /* TitleState_h */
