##
## EPITECH PROJECT, 2024
## arcade
## File description:
## Makefile
##

SRC = nibbler.cpp \

CPPFLAGS	=	-fPIC -W -Wall -Wextra -std=c++20

CC			=	g++ -g

OBJ			=	$(SRC:.cpp=.o)

NAME		=	../../../lib/arcade_nibbler.so

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
