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
LIBINC	=	 -I libs/list/ -I libs/strings

CFLAGS	=	$(INCFLAGS) $(LIBINC) -Wall -Wextra -Werror -O2

SRC	=	libs/list/list_generic_del.c      \
		libs/list/list_generic_display.c  \
		libs/list/list_generic_get.c      \
		libs/list/list_generic.c          \
		libs/strings/string_to_array.c    \
		src/ai_comm/ai_move.c             \
		src/ai_comm/ai_object.c           \
		src/ai_comm/ai_player_tool.c      \
		src/ai_comm/ai_elevation.c        \
		src/gui_comm/gui_comm.c           \
		src/gui_comm/gui_comm2.c          \
		src/gui_comm/item_msg.c           \
		src/gui_comm/map_team_msg.c       \
		src/gui_comm/player_event_msg.c   \
		src/gui_comm/player_msg.c         \
		src/gui_comm/server_msg.c         \
		src/gui_comm/time_msg.c           \
		src/map/map.c                     \
		src/map/egg.c                     \
		src/teams_tool/teams_tool.c       \
		src/main.c                        \
		src/client_handling.c             \
		src/client.c                      \
		src/struct_fnc.c                  \
		src/loop_server.c                 \
		src/networking.c                  \
		src/command_handler.c             \
		src/parsing_args.c                \
		src/server.c                      \
		src/game_update.c                 \
		src/time_management.c

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
