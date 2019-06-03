#include "../include/Collider.h"
#include "../include/Sprite.h"
#include "../include/Camera.h"

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated){
	this->scale = scale;
	this->offset = offset;
}
void Collider::Update(float dt){
	box = associated.box;
	box.w *= scale.x;
	box.h *= scale.y;
	Vec2 girado = offset;
	Sprite* spr = (Sprite*) associated.GetComponent("Sprite");
	girado.Rotacao(spr->angleDeg);
	box.x += offset.x;
	box.y += offset.y;
}
void Collider::Render() {
	// if(D_TRACE){
	// 	Vec2 center = new Vec2( box.GetCentro()->x, box.GetCentro()->y );
	// 	SDL_Point points[5];
	// 	Vec2 aux = Vec2::Subtracao(new Vec2(box.x, box.y), center);
	// 	aux.Rotacao( associated.angleDeg/(180/PI);
	// 	Vec2 point = Vec2::Subtracao(Vec2::Soma(aux, center), Camera::pos));
	// 	points[0] = {(int)point.x, (int)point.y};
	// 	points[4] = {(int)point.x, (int)point.y};
		
	// 	point = (Vec2(box.x + box.w, box.y) - center).Rotacao( associated.angleDeg/(180/PI) )
	// 					+ center - Camera::pos;
	// 	points[1] = {(int)point.x, (int)point.y};
		
	// 	point = (Vec2(box.x + box.w, box.y + box.h) - center).Rotacao( associated.angleDeg/(180/PI) )
	// 					+ center - Camera::pos;
	// 	points[2] = {(int)point.x, (int)point.y};
		
	// 	point = (Vec2(box.x, box.y + box.h) - center).Rotacao( associated.angleDeg/(180/PI) )
	// 					+ center - Camera::pos;
	// 	points[3] = {(int)point.x, (int)point.y};

	// 	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	// 	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
	// }
}
bool Collider::Is(std::string type){ return type == "Collider"; }
void Collider::SetScale(Vec2 scale){ this->scale = scale; }
void Collider::SetOffset(Vec2 offset){ this->offset = offset; }
Collider::~Collider(){}