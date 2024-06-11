##
## EPITECH PROJECT, 2024
## arcade
## File description:
## Makefile
##

SRC = sdl2.cpp \

CPPFLAGS	=	-fPIC -std=c++20 -W -Wall -Wextra `sdl2-config --cflags --libs` -lSDL2_ttf

CC			=	g++ -g

OBJ			=	$(SRC:.cpp=.o)

NAME		=	../../../lib/arcade_sdl2.so

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -shared $(CPPFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -rf *.so


fclean:	clean
	rm -f $(NAME)
	rm -rf *.so


re:	fclean all
