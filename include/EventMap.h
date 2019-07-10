#ifndef C_EVENTMAP
#define C_EVENTMAP

#include "inclusao.h"
#include "Component.h"
#include "Event.h"
#include <iostream>
#include <sstream>

class EventMap : public Component{

public:
	EventMap(GameObject&, int, int);
	~EventMap();

	void AddEvent(std::string, int, int, int, bool);					// Sem sprite
	void AddEvent(std::string, int, int, int, bool, std::string, int);	// Sprite próprio
	void AddEvent(std::string, int, int, int, bool, int);				// Sprite do tileset
	Event* At(int, int);
	Event* GetEvent(std::string);
	void RemoveEvent(std::string);

	void OuvirEventos(int);

	int GetWidth();
	int GetHeight();
	void SetWidth(int);
	void SetHeight(int);

	void Update(float);
	void Render();
	bool Is(std::string);
private:
	std::vector<Event*> eventMatrix;
	int mapWidth;
	int mapHeight;
};

#endif //C_EVENTMAP