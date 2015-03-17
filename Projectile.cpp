#ifndef SHOOT_1
#define SHOOT_1


#include "GameObject.cpp"
#include "Game.cpp"


class playerBullet: public GameObject {
public:
	char c;
	Game ggg;
	playerBullet(Game g, char c, int x, int y): c(c), GameObject::GameObject(c, x, y)
	{
		ggg = g;
	}
	


};

class enemyBullet: public GameObject {
public:
	char c;
	Game ggg;
	enemyBullet(Game g, char c, int x, int y): c(c), GameObject::GameObject(c, x, y)
	{
		ggg = g;
	}


};

#endif