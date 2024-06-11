##
## EPITECH PROJECT, 2024
## arcade
## File description:
## Makefile
##

SRC = sfml.cpp \

SFML_PATH = /opt/homebrew/opt/sfml/include

CPPFLAGS	=	-fPIC -std=c++20 -W -Wall -Wextra -lsfml-graphics -lsfml-window -lsfml-system


CC			=	g++ -g

OBJ			=	$(SRC:.cpp=.o)

NAME		=	../../../lib/arcade_sfml.so

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

macos: SFML_PATH = /opt/homebrew/opt/sfml/include

macos: CPPFLAGS = -fPIC -std=c++20 -W -Wall -Wextra -I $(SFML_PATH) -L /opt/homebrew/opt/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system

macos: $(NAME)
