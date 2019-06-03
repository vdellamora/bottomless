#ifndef C_STATE
#define C_STATE

#include "inclusao.h"
#include <iostream>
#include "GameObject.h"
#include <memory>

class State{

public:
	State();
	virtual ~State();
	void virtual LoadAssets();
	void virtual Update(float);
	void virtual Render();
	void virtual Start();
	void virtual Resume();
	void virtual Pause();

	std::weak_ptr<GameObject> virtual AddObject(GameObject*);
	std::weak_ptr<GameObject> virtual GetObjectPtr(GameObject*);

	bool PopRequested();
	bool QuitRequested();
protected:
	void StartArray();
	void virtual UpdateArray(float);
	void virtual RenderArray();

	bool popRequested;
	bool quitRequested;
	bool started;
	std::vector<std::shared_ptr<GameObject>> objectArray;

};

#endif //C_STATE