##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

CC	=	gcc
NAME	=	../zappy_server
LIBNAME=	libs/libmy.a

INCFLAGS	=	-I include
LIBINC	=	 -I libs/include

CFLAGS	=	$(INCFLAGS) $(LIBINC) -Wall -Wextra -Werror -O2


LIBSRC	=	libs/list/list_generic_del.c		\
			libs/list/list_generic_display.c	\
			libs/list/list_generic_get.c		\
			libs/list/list_generic.c			\

SRC	=	src/main.c

OBJ	=	$(SRC:.c=.o)
LIBOBJ	=	$(LIBSRC:.c=.o)

$(NAME):	$(LIBNAME)	$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

$(LIBNAME):	$(LIBOBJ)
	$(AR) cr -o $(LIBNAME) $(LIBOBJ)

all: $(NAME)

clean:
	rm -f $(OBJ)
	rm -f $(LIBOBJ)
	rm -f $(LIBNAME)
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

lint:
	mkdir -p __cppcheckWorkaroundInclude
	find . -type f \( -iname \*.h -o -iname \*.inl -o -iname \*.hpp \) -exec cp {} __cppcheckWorkaroundInclude \;
	cppcheck --enable=all --quiet --suppress=missingIncludeSystem \
		--suppress=constVariablePointer --suppress=variableScope --error-exitcode=1 --output-file=check.txt -I__cppcheckWorkaroundInclude .

.PHONY:	clean fclean re all debug asan fast lint
