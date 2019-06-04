#ifndef C_CECILIA
#define C_CECILIA

#include "inclusao.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Sprite.h"
#include <iostream>
#include <memory>

#define CECILIA_MOVE_SPEED 4
#define CECILIA_ANIMATION_SPEED 0.0908f

class GameObject;
class Cecilia : public Component{

public:
	Cecilia(GameObject&);
	~Cecilia();
	void Start();
	void Update(float);
	void Render();
	bool Is(std::string);

	static Cecilia* player;
	void NotifyCollision(GameObject&);
	void SetGrid(int, int);
	bool VaiColidir(int, int);
	// void Walk(int);

private:
	Sprite* spr;
	Vec2 speed;
	Vec2 grid;
	int nx;
	int ny;
	int hp;
	int direcao;
	int caminho;
	bool andando;
	bool parou;

	float dbg_tempoWalk;
};

#endif //C_CECILIA