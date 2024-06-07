##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

CC	=	gcc
NAME	=	../zappy_server
LIBNAME=	libs/libmy.a

INCFLAGS	=	-I include -I libs/list/ -I libs/strings
LDFLAGS	=	-Llibs -lmy

CFLAGS	=	$(INCFLAGS) -Wall -Wextra -Werror -O2

LIB_SRC	=	libs/list/list_generic_del.c      \
			libs/list/list_generic_display.c  \
			libs/list/list_generic_get.c      \
			libs/list/list_generic.c          \
			libs/strings/string_to_array.c

SRC	=	src/ai_comm/ai_move.c             \
		src/ai_comm/ai_object.c           \
		src/ai_comm/ai_player_tool.c      \
		src/ai_comm/ai_elevation.c        \
		src/ai_comm/ai_fork.c             \
		src/ai_comm/ai_look.c             \
		src/gui_comm/gui_comm.c           \
		src/gui_comm/gui_comm2.c          \
		src/gui_comm/map_team_msg.c       \
		src/gui_comm/player_msg.c         \
		src/gui_comm/time_msg.c           \
		src/events/gui_update.c           \
		src/events/gui_update2.c          \
		src/events/item_msg.c             \
		src/events/player_event_msg.c     \
		src/events/player_events.c        \
		src/events/server_msg.c           \
		src/map/map.c                     \
		src/map/egg.c                     \
		src/map/update_map.c              \
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
		src/time_management.c             \
		src/logger.c

LIB_OBJ	=	$(LIB_SRC:.c=.o)
OBJ	=	$(SRC:.c=.o)

$(NAME):$(LIBNAME) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

$(LIBNAME):	$(LIB_OBJ)
	$(AR) cr -o $(LIBNAME) $(LIB_OBJ)

all: $(LIBNAME) $(NAME)

clean:
	rm -f $(OBJ)
	rm -f $(OBJ:.o=.gcno)
	rm -f $(OBJ:.o=.gcda)
	rm -f $(TEST_NAME)
	rm -f $(TEST_OBJ)
	rm -f $(TEST_GCDA)
	rm -f $(TEST_GCNO)
	rm -f $(LIB_OBJ)
	rm -f coding-style-reports.log
	rm -f vgcore*
	find -name "*~" -type f -delete

fclean:	clean
	rm -f $(NAME)
	rm -f $(LIBNAME)

re:	fclean all

debug:	CFLAGS	+= -O0	-g3 -ggdb3 -Wpedantic
debug:	re

asan:	CFLAGS	+= -O0	-g3 -ggdb3 -Wpedantic -fsanitize=address\
	-fsanitize=undefined
asan:	re

TEST_SRC    =   tests/test_ai_move.c         \
				tests/test_ai_turn_right.c   \
				tests/test_ai_turn_left.c

TEST_OBJ    =   $(TEST_SRC:.c=.o)
TEST_GCDA   =   $(TEST_SRC:.c=.gcda)
TEST_GCNO   =   $(TEST_SRC:.c=.gcno)

TEST_NAME   =   test_run

CFLAGS +=    --coverage -lcriterion

test_run:	re	clean	$(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o $(TEST_NAME) -Wl,-rpath=.
	./$(TEST_NAME)	|| true
	gcovr

.PHONY:	clean fclean re all debug asan test_run
