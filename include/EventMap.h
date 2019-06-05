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

	Event At(int, int);
	void AddEvent(int, int, int, bool);
	void RemoveEvent(Event);


	int GetWidth();
	int GetHeight();
	void SetWidth(int);
	void SetHeight(int);

	void Render();
	bool Is(std::string);
private:
	std::vector<Event>eventMatrix;
	int mapWidth;
	int mapHeight;
};

#endif //C_EVENTMAP