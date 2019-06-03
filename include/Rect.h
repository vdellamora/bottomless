#ifndef C_RECT
#define C_RECT

#include "inclusao.h"
#include "Vec2.h"
#include <iostream>

class Rect{

public:
	Rect();
	Rect(float, float, float, float);
	~Rect();
	float GetWidth();
	float GetHeight();
	float GetX();
	float GetY();
	void Soma(Vec2*);
	Vec2* GetCentro();
	static float Distancia(Rect*, Rect*);
	bool IsInside(Vec2*);
	// TODO Operações soma, subt e atribuição
	float w;
	float h;
	float x;
	float y;
};

#endif //C_RECT