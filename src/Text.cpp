#include "../include/Text.h"
#include "../include/Game.h"
#include "../include/Camera.h"
#include "../include/Resources.h"
#include "../include/Rect.h"

Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color) : Component(associated){
	this->fontFile = fontFile;
	this->fontSize = fontSize;
	this->style = style;
	this->text = text;
	this->color = color;
	texture = nullptr;

	RemakeTexture();
}
Text::~Text(){if(texture != nullptr) SDL_DestroyTexture(texture);}
void Text::Render(){
	Rect box = associated.box;
	SDL_Rect source = {0,0,(int)box.w,(int)box.h};
	SDL_Rect dest = {(int)(box.x + Camera::pos.x), (int)(box.y + Camera::pos.y), source.w, source.h};
	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), 
		texture, &source, &dest, 
		0, nullptr, SDL_FLIP_NONE);
}
void Text::RemakeTexture(){
	if(texture != nullptr) SDL_DestroyTexture(texture);

	font = Resources::GetFont(fontFile,fontSize);
	SDL_Surface *surface = nullptr;
	if(style == TextStyle::SOLID) 
		surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
	else if(style == TextStyle::SHADED) 
		surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, {0,0,0,255});
	else if(style == TextStyle::BLENDED) 
		surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);

	texture = SDL_CreateTextureFromSurface(
		Game::GetInstance().GetRenderer(), surface);
	SDL_SetTextureAlphaMod(texture, color.a);

	if(surface){associated.box.w = surface->w; associated.box.h = surface->h;}
	SDL_FreeSurface(surface);
}

void Text::SetText(std::string text){this->text = text; RemakeTexture();}
void Text::SetColor(SDL_Color color){this->color = color; RemakeTexture();}
void Text::SetStyle(TextStyle style){this->style = style; RemakeTexture();}
void Text::SetFontFile(std::string fontFile){this->fontFile = fontFile;}
void Text::SetFontSize(int fontSize){this->fontSize = fontSize; RemakeTexture();}
void Text::Update(float dt){}
bool Text::Is(std::string type){return type == "Text";}