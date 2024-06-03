##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

NAME    =   zappy_ai

$(NAME):
	@echo "#!/usr/bin/env python3" > $(NAME)
	@cat src/ai.py >> $(NAME)
	@chmod 755 $(NAME)
	@cp $(NAME) ../
	@echo "Zappy-ai ✔"

all:	$(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
