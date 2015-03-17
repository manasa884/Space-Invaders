#ifndef G_OBJ
#define G_OBJ


#include <iostream>
#include <list>

class GameObject {
public:
	int x, y;
	char c;

	GameObject(char c, int x, int y): c(c), x(x), y(y) {}
	
	virtual void move(int ticks) {}
	
	int getX()
	{
		return x;
	}
	
	int getY() 
	{
		return y;
	}
	
	void setX(int nX)
	{
		x = nX;
	}
	
	void setY(int nY)
	{
		y = nY;
	}
	
	char getChar()
	{
		return c;
	}
	
		
	
	bool collideWith(GameObject other)
	{
		if(x == other.getX() && y == other.getY())
		{
			//printf("collision ");
			return true;
		}
		return false;
	}

};

#endif