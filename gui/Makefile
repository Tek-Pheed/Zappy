##
## EPITECH PROJECT, 2024
## GUI-Zappy
## File description:
## Makefile
##

NAME    =   zappy_gui

SRC		=	src/main.cpp

OBJ		=	$(SRC:.cpp=.o)

all:	$(NAME)

CFLAGS = -W -Wall -Wextra

LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

%.o: %.cpp
	g++ $(CFLAGS) $^-c -o $@

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re