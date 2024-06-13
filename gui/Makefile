##
## EPITECH PROJECT, 2024
## GUI-Zappy
## File description:
## Makefile
##

NAME    =   zappy_gui

SRC		= src/main.cpp \
		  src/Menu.cpp \
		  src/Utils.cpp \
		  src/Input.cpp \
		  src/Settings.cpp \
		  src/Draw.cpp \
		  src/AItems.cpp \
		  src/Items/Food.cpp \
		  src/Items/Deraumere.cpp \
		  src/Items/Linemate.cpp \
		  src/Items/Mendiane.cpp \
		  src/Items/Phiras.cpp \
		  src/Items/Sibur.cpp \
		  src/Items/Thystame.cpp \
		  src/ConfirmButton.cpp	\

OBJ		=	$(SRC:.cpp=.o)

CFLAGS = -W -Wall -Wextra -I./include

LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lX11

%.o: %.cpp
	g++ $(CFLAGS) $^ -c -o $@

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(LDFLAGS)
	@cp $(NAME) ../

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
