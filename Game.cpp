#ifndef GAME_1
#define GAME_1

#include "GameObject.cpp"

#include <iostream>
#include <list>

using namespace std;

class Game {
public:
	
	
	list<GameObject*> objs;
	list<GameObject*> rems;
	GameObject *p;
	int eCount;
	int bCount;
	bool deadPlayer;
	Game() {
		deadPlayer = true;
		bCount = 0;
	}

	//methods
	void removeObject(GameObject *obj)
	{
		if(obj->c == '|')
		{
			bCount = bCount - 1;
		}
		rems.push_back(obj);
	}

	void notifyDeadPlayer(bool b) {
		deadPlayer = b;
	}
	

	void notifyDeadEnemy() {
		eCount--;
		if(eCount == 0)
		{
			notifyDeadPlayer(true);
		}

	}

	
};
	
#endif
