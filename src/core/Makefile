##
## EPITECH PROJECT, 2024
## arcade
## File description:
## Makefile
##

SRC	=	main.cpp

NAME	=	../../arcade

OBJ	= $(SRC:.cpp=.o)

CXXFLAGS	= -I./includes/ -std=c++20  -Wall -Wextra -fPIC -g -std=c++20

all: $(NAME)

$(NAME):	$(OBJ)
	g++ -g $(OBJ) -o $(NAME) $(CXXFLAGS)

debug:	fclean $(OBJ)
	g++ -g $(SRC) -o $(NAME) $(CXXFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
