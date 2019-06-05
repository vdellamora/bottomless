#ifndef C_EVENT
#define C_EVENT

#include "inclusao.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Sprite.h"
#include <iostream>
#include <memory>

class GameObject;
class Event : public Component{

public:
	Event(GameObject&);
	Event(GameObject&, int, bool);
	Event(GameObject&, int, bool, std::string);
	~Event();
	void Start();
	void Update(float);
	void Render();
	bool Is(std::string);

	void Execute();
	void NotifyCollision(GameObject&);
	void SetGrid(int, int);
	Vec2 GetGrid();
	bool GetSolido();
	int GetType();

	bool vazio;

private:
	enum EventType {PRESS, TOUCH};
	EventType type;
	Sprite* spr;
	Vec2 speed;
	Vec2 grid;
	int direcao;

	int caminho;
	bool andando;
	bool parou;
	bool solido;
};

#endif //C_EVENT