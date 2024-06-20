##
## EPITECH PROJECT, 2024
## GUI-Zappy
## File description:
## Makefile
##

NAME    =   zappy_gui

SRC		= src/main.cpp \
		  src/Menu.cpp \
		  src/Input.cpp \
		  src/Settings.cpp \
		  src/Draw.cpp \
		  src/Parser.cpp \
		  src/Player.cpp \
		  src/VectorPlayers.cpp \
		  src/Map.cpp \
		  src/Bloc.cpp \
		  src/ConfirmButton.cpp	\
		  src/Server.cpp \
		  src/RessourcePool.cpp \
		  src/Thread.cpp

OBJ		=	$(SRC:.cpp=.o)

CFLAGS = -W -Wall -Wextra -I./include -std=c++20 -g3

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
	rm -rf ../$(NAME)

re: fclean all

debug:	CFLAGS	+= -O0	-g3 -ggdb3 -Wpedantic
debug:	re

asan: CFLAGS += -g3 -fsanitize=address
asan: LDFLAGS += -fsanitize=address
asan: re

.PHONY: all clean fclean asan re
