#ifndef C_EVENT
#define C_EVENT

#include "inclusao.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Action.h"
#include <iostream>
#include <memory>
#include <queue>

class GameObject;
class Action;
class Event : public Component{

public:
	Event(GameObject&);
	Event(GameObject&, std::string, int, bool);
	Event(GameObject&, std::string, int, bool, std::string); // Sprite próprio
	Event(GameObject&, std::string, int, bool, int);		 // Sprite do TileSet
	~Event();
	void Start();
	void Update(float);
	void Render();
	bool Is(std::string);
	void NotifyCollision(GameObject&);

	void NewAction(Action*);
	void Execute();
	void Ouvir(int);

	void Move(int, int);
	bool VaiColidir(int, int);
	void SetGrid(int, int);
	Vec2 GetGrid();
	bool GetSolido();
	int GetType();
	std::string GetIdentifier();

	bool vazio;

private:
	std::vector<Action*> listaAcoes;

	enum EventType {PRESS, TOUCH};
	EventType type;
	Vec2 grid;
	Sprite* spr;
	std::string identifier;
	int tileNumber;
	int direcao;
	int velocidade;

	int nx, ny;
	int caminho;
	bool andando;
	bool parou;
	bool solido;
};

#endif //C_EVENT