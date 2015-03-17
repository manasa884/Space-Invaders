/** 
Name: <your name>
Eid: <your id>
*/

#include <ncurses.h>    // the ncurses library
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <unistd.h> // sleep
#include <list>
#include "timehelper.cpp"
#include "GameObject.cpp"
#include "Ship.cpp"
#include "Game.cpp"
#include "Projectile.cpp"

using namespace std;

int main (int argc, char const *argv[])
{
	
    srand (time(NULL)); /// seed to some random number based on time
    if ( initscr() == NULL ) { /// init the screen, defaults to stdscr
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(EXIT_FAILURE);
    }


    noecho(); /// don't echo keypresses
    keypad(stdscr, TRUE); /// set the keypad to stdscr
    nodelay(stdscr, false);
    curs_set(0); /// set cursor to invisible (if allowed by the os)
    const int delay = 90; /// milliseconds
    timeout(delay); /// set how long between keypresses (more or less)

    /// some variables to give you some hints
    int ch = 0;
    bool quit = false;
    int points = 0;
    int x = 17;
    int y = 22;
    int elapsedTime = getElapsedTime();
	

	// added variables
	int ticks = 0;
	int ROWS = 22;
	int COLS = 37;
	Game *g = new Game();
	
	bool &deadPlayer = g->deadPlayer;
	
	//boundaries
	int bUP = 3;
	int bDOWN = 22;
	int bRIGHT = 1;
	int bLEFT = 35;
	
	
	//object lists
	list<GameObject*> objects;
	list<GameObject*> remList;
	GameObject *player ;
	int &enemyCount = g->eCount;
	
	
	
	//init objects
	player = new Ship(*g, '^', x, y);
	g->objs.push_back(player);	
	enemyCount = 0;
	for(int row = 3; row < 6; row = row + 2)
	{
		for(int col = 8; col < 29; col = col + 2) 
		{
			if(col % 4 == 0)
			{
				Ship *w = new Ship(*g, 'W', col, row);
				g->objs.push_back(w);
				enemyCount++;
			}
			else 
			{
				Ship *u = new Ship(*g, 'u', col, row);
				g->objs.push_back(u);
				enemyCount++;
			}
		}
	}
	

    while (!quit && deadPlayer){
		
		ticks++;
        ch = getch();
        erase(); /// erase the screen (after getch())
        if ( ch != ERR) { /// user has a keypress
            /// this is to delay until the next tick
            elapsedTime = getElapsedTime();
            if (elapsedTime < delay)
			{
                nsleep(delay-elapsedTime);
			}
        }


        // this is how to print a string to the screen, 0, 0 is the  y, x location
        mvprintw(0, 0, "Points: %i.   'q' to quit.\n", points);
		// attroff(COLOR_PAIR(1));
        
		mvprintw(25, 0, "Bullet Count: %i.   'q' to quit.\n", 5 - g->bCount);
		
		
		
		//win message
		if(points == 22)
		{
			player->c = '*';
	        mvprintw(11, 14, "~~~~~~~~", points);
	        mvprintw(15, 14, "~~~~~~~~", points);
	        mvprintw(13, 14, "You Win!", points);
		}
		
		char screen[22][38] = {
			" ___________________________________ ",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|                                   |",
			"|___________________________________|"
		};
		
		for(int i = 2; i < ROWS + 2; i++) {
			for(int j = 0; j < COLS; j++) {
				if(screen[i - 2][j] == '_' || screen[i - 2][j] == '|') {
					mvaddch(i, j, screen[i - 2][j]);
				}
			}
		}
		
		

        /// some example code to show how to work with the keyboard
        switch(ch){
                case KEY_UP:
				{
					if(y > bUP)
					{
						y--;
						player->setY(y);
					} 
				}
					break;
                case KEY_RIGHT: 
				{
					if(x < bLEFT)
					{
						x++;
						player->setX(x);
						
					}	 
				}
					break;
                case KEY_DOWN: 
				{
					if(y < bDOWN)
					{
						y++;
						player->setY(y);
							
					}
				}
					break;
                case KEY_LEFT:
				{
					if(x > bRIGHT) 
					{
						x--;
						player->setX(x);
						
					}
				}
					break;
                case ' ':
				{
					if(g->bCount < 5)
					{
						playerBullet *b = new playerBullet(*g, '|', player->getX(), player->getY());
						g->objs.push_back(b);
						g->bCount = g->bCount + 1;
					}
				}
                    break;
                case 'q': 
                    quit = true;
                    break;
        }

        mvaddch(y,x,'^'); // example print a char to the screen at the y, x location

		//add objects
		for(list<GameObject*>::iterator it = g->objs.begin(); it != g->objs.end(); ++it)
		{
			GameObject *temp = *it;
			Ship *ss = dynamic_cast<Ship*>(temp);
			if(ss != 0)
			{
				ss->move(ticks);
			}
			
			playerBullet *pb = dynamic_cast<playerBullet*>(temp);
			if(pb != 0)
			{
				if(temp->getY() == 3)
				{
					g->removeObject(pb);
				}
				else 
				{
					temp->GameObject::setY(temp->GameObject::getY() - 1);
					
				}
				
			}
			mvaddch(temp->getY(), temp->getX(), temp->getChar());
			
			enemyBullet *eb = dynamic_cast<enemyBullet*>(temp);
			if(eb != 0)
			{
				if(temp->getY() == 22)
				{
					g->removeObject(eb);
				}
				else 
				{
					temp->GameObject::setY(temp->GameObject::getY() + 1);
					
				}
			}
			mvaddch(temp->getY(), temp->getX(), temp->getChar());
			
		}
		
		
		for(list<GameObject*>::iterator it = g->objs.begin(); it != g->objs.end(); ++it)
		{
			GameObject *o = *it;
				if(o->c == 'W')
				{
					bool chance = (rand() % 100) < 0.55;
					if(chance)
					{
						enemyBullet *b = new enemyBullet(*g, '!', o->getX(), o->getY());
						g->objs.push_back(b);
						
					}
				}
		
				if(o->c == 'u')
				{
					bool chance = (rand() % 100) < 0.08;
					if(chance)
					{
						enemyBullet *b = new enemyBullet(*g, '!', o->getX(), o->getY());
						g->objs.push_back(b);
					}
				}
		}
				
		//collisions
		for(list<GameObject*>::iterator it = g->objs.begin(); it != g->objs.end(); ++it)
		{
			for(list<GameObject*>::iterator ij = g->objs.begin(); ij != g->objs.end(); ++ij)
			{
				GameObject *one = *it;
				GameObject *two = *ij;
				
				if(one->c == two->c && one->getX() == two->getX() && one->getY() == two->getY())
				{
					break;
				}
				if(one->collideWith(*two))
				{
					//player bullet & enemy ship
					if(one->c == '|' && (two->c == 'W' || two->c == 'u'))
					{
						g->removeObject(one);
						g->removeObject(two);
						g->notifyDeadEnemy();
						++points;
					}
					else if((one->c == 'W' || one->c == 'u') && two->c == '|')
					{
						g->removeObject(one);
						g->removeObject(two);
						g->notifyDeadEnemy();
						++points;
						
					}
					
					else if (one->c == '^' && (two->c == 'W' || two->c == 'u'))
					{
						g->removeObject(one);
						g->removeObject(two);
						quit = true;
					}	
					else if (two->c == '^' && (one->c == 'W' || one->c == 'u'))
					{
						g->removeObject(one);
						g->removeObject(two);
						quit = true; 
					}	
					
					else if (two->c == '^' && one->c == '!')
					{
						g->removeObject(one);
						g->removeObject(two);
						quit = true; 
					}	
						
					else if (two->c == '!' && one->c == '^')
					{
						g->removeObject(one);
						g->removeObject(two);
						quit = true; 
					}
					
					else if (two->c == '!' && one->c == '|')
					{
						g->removeObject(one);
						g->removeObject(two);
					}		
							
					else if (two->c == '|' && one->c == '!')
					{
						g->removeObject(one);
						g->removeObject(two);
					}		
					
						
				}
			}
		}
		
		
		//remove objects
		for(list<GameObject*>::iterator it = g->rems.begin(); it != g->rems.end(); ++it)
		{
			g->objs.remove(*it);
		}
		
        refresh(); // refresh the screen after adding everything
        move(0,0); /// move cursor to 0,0 (looks prettier if os doesn't allow invisible cursors)
    }   
    
	
    endwin();   /// cleanup the window

    return 0;
}