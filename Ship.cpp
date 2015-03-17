#ifndef SHIP_1
#define SHIP_1


#include <iostream>
#include "GameObject.cpp"
#include <list>
#include "Game.cpp"
#include "Projectile.cpp"

using namespace std;


class Ship: public GameObject{
public:
	
	char c;
	int direction;
	Game g;
	Ship(Game g, char c, int x, int y): GameObject::GameObject(c, x, y), c(c)
	{
		// GameObject::GameObject(c, x, y);
		direction = -1;
	}
	
	
	void move(long ticks)
	{
		if(c == '^')
		{
			return;
		}
		if(ticks % 20 != 0)
		{
			return;
		}
		//shoot(ticks);
		if(GameObject::getY() >= 21 )
		{
			return;
			g.notifyDeadPlayer(true);
		}
		if(GameObject::getX() == 1 && direction < 0)
		{
			direction = 1;
			GameObject::setY(GameObject::getY() + 1);
		}
		if(GameObject::getX() == 35 && direction > 0)
		{
			direction = -1;
			GameObject::setY(GameObject::getY() + 1);
		}
		if(GameObject::getX() > 1 && direction < 0)
		{
			GameObject::setX(GameObject::getX() - 1);
		}
		else if(GameObject::getX() < 35 && direction > 0)
		{
			GameObject::setX(GameObject::getX() + 1);
		}
		
	}

	// void shoot(int ticks)
	// {
	// 	if(c == 'W')
	// 	{
	// 		enemyBullet *b = new enemyBullet(g, '!', GameObject::getX(), GameObject::getY());
	// 		g.objs.push_back(b);
	// 	}
	//
	// 	if(c == 'u')
	// 	{
	// 		if(ticks % 3 == 0)
	// 		{
	// 			enemyBullet *b = new enemyBullet(g, '!', GameObject::getX(), GameObject::getY());
	// 			g.objs.push_back(b);
	// 		}
	// 	}
	//
	// }
	
};


#endif