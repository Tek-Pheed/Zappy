##
## EPITECH PROJECT, 2024
## GroundHog
## File description:
## Makefile
##

NAME    =   zappy_gui

SRC		=	src/

OBJ		=	$(SRC:.cpp=.o)

all:	$(NAME)

CFLAGS = -W -Wall -Wextra

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) -o $(CFLAGS)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re