##
## EPITECH PROJECT, 2024
## GUI-Zappy
## File description:
## Makefile
##

NAME    =   zappy_gui

SRC		= src/main.cpp \
		  src/Utils.cpp \
		  src/Draw.cpp \
		  src/AItems.cpp \
		  src/Items/Food.cpp \
		  src/Items/Deraumere.cpp \
		  src/Items/Linemate.cpp \
		  src/Items/Mendiane.cpp \
		  src/Items/Phiras.cpp \
		  src/Items/Sibur.cpp \
		  src/Items/Thystame.cpp \

OBJ		=	$(SRC:.cpp=.o)

CFLAGS = -W -Wall -Wextra -I./include

LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

%.o: %.cpp
	g++ $(CFLAGS) $^ -c -o $@

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
