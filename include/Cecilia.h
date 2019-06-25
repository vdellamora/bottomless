#ifndef C_CECILIA
#define C_CECILIA

#include "inclusao.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Event.h"
#include <iostream>
#include <memory>

#define CECILIA_MOVE_SPEED 4
#define CECILIA_IDLE_SPEED 0.2f
#define CECILIA_ANIMATION_SPEED 0.0908f

class GameObject;
class Cecilia : public Component{

public:
	static Cecilia* player;
	Cecilia(GameObject&);
	~Cecilia();
	void Start();
	void Update(float);
	void Render();
	bool Is(std::string);
	void NotifyCollision(GameObject&);

	void Move(int);
	void SetGrid(int, int);
	bool VaiColidir(int, int);
	void VaiInteragir(int, int);
	int GetDirection();
	// void Walk(int);

	void TocarSom();
	void InfligirDano(int);

private:
	Sprite* spr;
	Vec2 speed;
	Vec2 grid;
	int nx;
	int ny;
	int direcao;
	int direcaoAnterior;
	int caminho;
	bool andando;
	bool parou;

	int hp;
	int audioSelecionado;

	Event* eventoPraExecutar;
	float dbg_tempoWalk;
};

#endif //C_CECILIA