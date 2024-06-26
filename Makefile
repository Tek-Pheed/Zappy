##
## EPITECH PROJECT, 2024
## Zappy
## File description:
## Makefile
##

MAKEFLAGS += --no-print-directory

all: server ai gui

server:
	@make -C ./server/
	@echo "Zappy-Server ✔"

ai:
	@make -C ./ai/

gui:
	@make -C ./gui/
	@echo "Zappy-gui ✔"

clean:
	@make clean -C ./server/
	@make clean -C ./ai/
	@make clean -C ./gui/
	@echo "Clean ✔"

fclean: clean
	@make fclean -C ./server/
	@make fclean -C ./ai/
	@make fclean -C ./gui/
	@rm -rf "zappy_ai"
	@rm -rf "zappy_server"
	@rm -rf "zappy_gui"
	@echo "FClean ✔"

debug:
	@make debug -C ./server/
	@make debug -C ./gui/
	@echo "Debug ✔"

re: fclean all

.PHONY: server ai gui all clean fclean debug re
