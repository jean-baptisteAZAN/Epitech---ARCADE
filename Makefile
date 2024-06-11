##
## EPITECH PROJECT, 2023
## make
## File description:
## make
##

all:
	make -C src/libs/ncurse
	make -C src/libs/sdl2
	make -C src/libs/sfml
	make -C src/game
	make -C src/core

core :
	make -C src/core

games :
	make -C src/game

graphicals :
	make -C src/libs/ncurse
	make -C src/libs/sdl2
	make -C src/libs/sfml

clean:
	make clean -C src/libs/ncurse
	make clean -C src/libs/sdl2
	make clean -C src/libs/sfml
	make clean -C src/game
	make clean -C src/core


fclean: clean
	make fclean -C src/libs/ncurse
	make fclean -C src/libs/sdl2
	make fclean -C src/libs/sfml
	make fclean -C src/game
	make fclean -C src/core

macos:
	make -C src/libs/ncurse
	make -C src/libs/sdl2
	make macos -C src/libs/sfml
	make -C src/game
	make -C src/core


re:	fclean all
