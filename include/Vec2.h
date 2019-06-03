#ifndef C_Vec2
#define C_Vec2

#include "inclusao.h"
#include <iostream>
#include <ostream>
#include <cmath>
class Vec2{

public:
	Vec2();
	Vec2(float, float);
	~Vec2();
	float GetX();
	float GetY();

	float GetMagnitude();
	Vec2 GetNormalizado();
	float GetInclinacao();
	static Vec2 Soma(Vec2*, Vec2*);
	static Vec2 Soma(Vec2, Vec2*);
	static Vec2 Subtracao(Vec2*, Vec2*);
	static Vec2 Subtracao(Vec2&, Vec2&);
	static Vec2 Subtracao(Vec2, Vec2*);
	Vec2 MultEscalar(Vec2*, float);
	static Vec2 MultEscalar(Vec2&, float);
	static float Distancia(Vec2*, Vec2*);
	static float InclinacaoReta(Vec2*, Vec2*);
	void Rotacao(float);
	float x;
	float y;

	friend std::ostream& operator<<(std::ostream& os, const Vec2& v);
};

#endif //C_Vec2