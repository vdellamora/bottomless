#include "../include/Rect.h"
Rect::Rect(){}
Rect::Rect(float x, float y, float w, float h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;

	if(w<0){
		x = x+w;
		w = w*(-1);
	}

	if(h<0){
		y = y+h;
		h = h*(-1);
	}
}
Rect::~Rect(){}
float Rect::GetWidth(){return w;}
float Rect::GetHeight(){return h;}
float Rect::GetX(){return x;}
float Rect::GetY(){return y;}
void Rect::Soma(Vec2* v){
	x+=v->GetX();
	y+=v->GetY();
}
Vec2* Rect::GetCentro(){
	return new Vec2(x+w/2, y+h/2);
}
float Rect::Distancia(Rect* r1, Rect* r2){
	return Vec2::Distancia(r1->GetCentro(), r2->GetCentro());
}
bool Rect::IsInside(Vec2* v){
	float vx, vy;
	vx=v->GetX();
	vy=v->GetY();

	if((vx>=x) && (vx<=x+w)){
		if((vy>=y) && (vy<=y+h)){
			return true;
		}
	}
	return false;

}
// TODO Operações soma, subt e atribuição