##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

MAKEFLAGS += --no-print-directory

server: $(OBJ)
	@make -C ./server/
	@echo "Zappy-Server ✔"

ai:
	@make -C ./ai/
	@echo "Zappy-ai ✔"

gui:
	@make -C ./gui/
	@echo "Zappy-gui ✔"

all: server ai gui

clean:
	@make clean -C ./server/
	@make clean -C ./ai/
	@make clean -C ./gui/
	@echo "Clean ✔"

fclean: clean
	@make fclean -C ./server/
	@make fclean -C ./ai/
	@make fclean -C ./gui/
	@echo "FClean ✔"

re: fclean all

.PHONY: server ai gui all clean fclean re