#include "../include/Dialogue.h"
#include "../include/Game.h"
#include "../include/Camera.h"
#include "../include/Resources.h"
#include "../include/Rect.h"

Dialogue::Dialogue(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color) : Component(associated){
  this->fontFile = fontFile;
  this->fontSize = fontSize;
  this->style = style;
  this->text = text;
  this->partialText = "";
  this->index = 0;
  this->color = color;
  this->textSpeed = 0.4/3; // medium
  texture = nullptr;
  
  this->shouldRender = true;
  
  RemakeTexture();
}
Dialogue::~Dialogue(){if(texture != nullptr) SDL_DestroyTexture(texture);}
void Dialogue::Render(){
  if (!shouldRender) return;
  Rect box = associated.box;
  SDL_Rect source = {0,0,(int)box.w,(int)box.h};
  SDL_Rect dest = {(int)(box.x + Camera::pos.x), (int)(box.y + Camera::pos.y), source.w, source.h};
  SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),
                   texture, &source, &dest,
                   0, nullptr, SDL_FLIP_NONE);
}
void Dialogue::RemakeTexture(){
  if(texture != nullptr) SDL_DestroyTexture(texture);
  
  font = Resources::GetFont(fontFile,fontSize);
  SDL_Surface *surface = nullptr;
  if(style == TextStyle::SOLID)
    surface = TTF_RenderText_Solid(font.get(), partialText.c_str(), color);
  else if(style == TextStyle::SHADED)
    surface = TTF_RenderText_Shaded(font.get(), partialText.c_str(), color, {0,0,0,255});
  else if(style == TextStyle::BLENDED)
    surface = TTF_RenderText_Blended(font.get(), partialText.c_str(), color);
  
  texture = SDL_CreateTextureFromSurface(
                                         Game::GetInstance().GetRenderer(), surface);
  SDL_SetTextureAlphaMod(texture, color.a);
  
  if(surface){associated.box.w = surface->w; associated.box.h = surface->h;}
  SDL_FreeSurface(surface);
}

void Dialogue::SetText(std::string text){
  this->text = text;
  this->index = 0;
  this->partialText.clear();
  this->partialText.resize(text.size());
  RemakeTexture();
}

void Dialogue::SetColor(SDL_Color color){this->color = color; RemakeTexture();}
void Dialogue::SetStyle(TextStyle style){this->style = style; RemakeTexture();}
void Dialogue::SetFontFile(std::string fontFile){this->fontFile = fontFile;}
void Dialogue::SetFontSize(int fontSize){this->fontSize = fontSize; RemakeTexture();}

void Dialogue::Update(float dt){
  printf("dialogue update\n");
  timer.Update(dt);
  if (index < text.size()){
    if (timer.Get() > textSpeed){
      shouldRender = true;
      timer.Restart();
      partialText.push_back(text.at(index)); // adiciona mais 1 caractere ao texto
      index++;
      // codigo pra pular linha (inserir \n?)
      RemakeTexture(); // refaz texto;
    }
  } else {
    if (timer.Get() > textSpeed*2){
      timer.Restart();
      shouldRender = !shouldRender;
    }
  }
}
// 1,2,3,4,5
void Dialogue::SetTextSpeed(int s){
  textSpeed = 0.4/s;
}

bool Dialogue::Is(std::string type){return type == "Dialogue";}
