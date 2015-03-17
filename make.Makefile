#	declare	variables
CC	=	g++	-g	-O0
LIBS	=	-lncurses
#	a	set	of	rules
#	no	spaces!!	only	tabs
all:
	${CC}	GameObject.cpp	Projectile.cpp	Ship.cpp	Game.cpp	main.cpp	${LIBS}
clean:
		rm	*.o
		rm	-rf	a.out.dSYM