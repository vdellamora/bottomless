#ifndef C_CECILIA
#define C_CECILIA

#include "inclusao.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Event.h"
#include <iostream>
#include <memory>
#include <set>
#define CECILIA_TILE_SIZE 96
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
	void SetGrid(int, int);
	void NotifyCollision(GameObject&);
	void InfligirDano(int);

	void Move(int);
	bool VaiColidir(int, int);
	void VaiInteragir(int, int);
	bool GetParouMovimento();
	int GetDirection();
	// void Walk(int);

	void PrepararGravador();
	void AddSound(int);
	void TocarSom();
	bool GetGravando();

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
	bool danoo;
	int audioSelecionado;
	bool gravando;
	std::set<int> bancoDeSons;

	Event* eventoPraExecutar;
	float dbg_tempoWalk;
};

#endif //C_CECILIA
