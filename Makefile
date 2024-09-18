##
## EPITECH PROJECT, 2024
## arcade
## File description:
## Makefile
##

core:
	make -C Core
	mv Core/arcade .

games:
	make -C Game/Snake
	mv Game/Snake/arcade_snake.so ./lib
	make -C Game/Ratio
	mv Game/Ratio/arcade_ratio.so ./lib
	make -C Game/Centipede
	mv Game/Centipede/arcade_centipede.so ./lib

graphicals:
	make -C Graphical/SFML
	mv Graphical/SFML/arcade_sfml.so ./lib
	make -C Graphical/NCurse
	mv Graphical/NCurse/arcade_ncurses.so ./lib
	make -C Graphical/SDL2
	mv Graphical/SDL2/arcade_sdl2.so ./lib

all: games core graphicals

clean:
	make -C Graphical/SFML clean
	make -C Graphical/NCurse clean
	make -C Graphical/SDL2 clean
	make -C Game/Snake clean
	make -C Game/Ratio clean
	make -C Game/Centipede clean
	make -C Core clean

fclean:
	make -C Graphical/SFML fclean
	make -C Graphical/NCurse fclean
	make -C Graphical/SDL2 fclean
	make -C Game/Snake fclean
	make -C Game/Ratio fclean
	make -C Game/Centipede fclean
	make -C Core fclean
	rm ./lib/*.so -f
	rm ./arcade_menu.so -f
	rm ./arcade -f

re: fclean all

# Cible par défaut
.DEFAULT_GOAL := all

.PHONY: all games core graphicals re clean fclean
