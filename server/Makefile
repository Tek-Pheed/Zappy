##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

CC	=	gcc
NAME	=	../zappy_server
LIBNAME=	libs/libmy.a

INCFLAGS	=	-I include
LIBINC	=	 -I libs/list/

CFLAGS	=	$(INCFLAGS) $(LIBINC) -Wall -Wextra -Werror -O2

SRC	=	libs/list/list_generic_del.c		\
		libs/list/list_generic_display.c	\
		libs/list/list_generic_get.c		\
		libs/list/list_generic.c			\
		src/main.c							\
		src/init_struct.c					\
		src/parsing_args.c					\
		src/loop_server.c					\
		src/server.c						\
		src/map.c							\
		src/networking.c					\
		src/client_handling.c
		src/map_team_msg.c	\
		src/player_msg.c

OBJ	=	$(SRC:.c=.o)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJ)
	rm -f $(OBJ:.o=.gcno)
	rm -f $(OBJ:.o=.gcda)
	rm -f coding-style-reports.log
	rm -f vgcore*
	find -name "*~" -type f -delete

fclean:	clean
	rm -f $(NAME)

re:	fclean all

debug:	CFLAGS	+= -O0	-g3 -ggdb3 -Wpedantic
debug:	re

asan:	CFLAGS	+= -O0	-g3 -ggdb3 -Wpedantic -fsanitize=address\
	-fsanitize=undefined
asan:	re

.PHONY:	clean fclean re all debug asan fast lint
