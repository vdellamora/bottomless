#include "../include/Vec2.h"

Vec2::Vec2(){}
Vec2::Vec2(float x, float y){
	this->x = x;
	this->y = y;
}
Vec2::~Vec2(){}
float Vec2::GetX(){return x;}
float Vec2::GetY(){return y;}

float Vec2::GetMagnitude(){
	return sqrt(x*x + y*y);
}
Vec2 Vec2::GetNormalizado(){
	return Vec2(x/GetMagnitude(),y/GetMagnitude());
}
float Vec2::GetInclinacao(){
	return atan2(y,x);
}
Vec2 Vec2::Soma(Vec2* v1, Vec2* v2){
	return Vec2(v1->GetX()+v2->GetX(), v1->GetY()+v2->GetY());
}
Vec2 Vec2::Soma(Vec2 v1, Vec2* v2){
	return Vec2(v1.GetX()+v2->GetX(), v1.GetY()+v2->GetY());
}
Vec2 Vec2::Subtracao(Vec2* v1, Vec2* v2){
	return Vec2(v1->GetX()-v2->GetX(), v1->GetY()-v2->GetY());
}
Vec2 Vec2::Subtracao(Vec2& v1, Vec2& v2){
	return Vec2(v1.GetX()-v2.GetX(), v1.GetY()-v2.GetY());
}
Vec2 Vec2::Subtracao(Vec2 v1, Vec2* v2){
	return Vec2(v1.GetX()-v2->GetX(), v1.GetY()-v2->GetY());
}
Vec2 Vec2::MultEscalar(Vec2* v1, float valor){
	return Vec2(v1->GetX()*valor, v1->GetY()*valor);
}
Vec2 Vec2::MultEscalar(Vec2& v1, float valor){
	return Vec2(v1.GetX()*valor, v1.GetY()*valor);
}
float Vec2::Distancia(Vec2* v1, Vec2* v2){
	return Vec2::Subtracao(v1, v2).GetMagnitude();
}
float Vec2::InclinacaoReta(Vec2* v1, Vec2* v2){
	return Vec2::Subtracao(v1, v2).GetInclinacao();
}
void Vec2::Rotacao(float t){
	// t>0: Sentido horário
	// printf("x = %f\n", x);
	// printf("y = %f\n", y);
	float nx = x*cos(t) - y*sin(t);
	float ny = y*cos(t) + x*sin(t);
	x = nx;
	y = ny;
	// printf("x = %f\n", x);
	// printf("y = %f\n", y);
	// printf("magnitude = \n",this->GetMagnitude());
}
std::ostream& operator<<(std::ostream& os, const Vec2& v){
	os << "(" << v.x << ", " << v.y << ")";
	return os;
}