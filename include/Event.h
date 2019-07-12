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

#define EVENT_TILE_SIZE 96
#define EVENT_IDLE_SPEED 0.2f

class GameObject;
class Action;
class Event : public Component{

public:
	Event(GameObject&);
	Event(GameObject&, std::string, int, bool);
	Event(GameObject&, std::string, int, bool, std::string, int); // Sprite próprio
	Event(GameObject&, std::string, int, bool, int);		 // Sprite do TileSet
	~Event();
	void Start();
	void Update(float);
	void Render();
	bool Is(std::string);
	void NotifyCollision(GameObject&);

	void NewAction(Action*);
	void ClearActions();
	bool GetExecutando();
	void Execute();
	void Execute(int);

	void Move(int, int);
	bool GetParouMovimento();
	bool VaiColidir(int, int);
	void SetGrid(int, int);
	Vec2 GetGrid();
	void SetSolido(bool);
	bool GetSolido();
	int GetType();
	void SetSomPedido(int);
	int GetSomPedido();

	void SetIdentifier(std::string);
	std::string GetIdentifier();
	GameObject& GetAssociated();
	bool vazio;

private:
	std::vector<Action*> listaAcoes;
	enum EventType {PRESS, TOUCH, LISTEN};
	int type;
	int somPedido;
	bool executando;
	int eventoAtual;
	// std::vector<Action*>::iterator eventoAtual;

	std::string identifier;
	int tileNumber;
	Sprite* spr;
	Vec2 grid;
	int direcao;
	int velocidade;

	int nx, ny;
	int caminho;
	bool andando;
	bool parou;
	bool solido;
};

#endif //C_EVENT
