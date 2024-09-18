##
## EPITECH PROJECT, 2024
## arcade
## File description:
## Makefile
##

##
## EPITECH PROJECT, 2024
## B-OOP-400-BAR-4-1-tekspice-ambroise.jacquemet-ramirez-vega
## File description:
## Makefile
##

CC			= g++

CPPFLAGS	=	-Wall -Wextra -std=c++20 -fPIC -fno-gnu-unique
CPPFLAGS	+=	-iquote include -iquote ../Common/include -iquote ../../Common/include

SRC			=	src/SnakeGame.cpp	\
				src/SnakeMenu.cpp	\
				src/Snake.cpp		\
				src/SnakeFactory.cpp	\
				../../Common/src/AObject.cpp

OBJ			=	$(SRC:.cpp=.o)

BINARY		=	arcade_snake.so

all: $(BINARY)

$(BINARY): $(OBJ)
	$(CC) -shared $(OBJ) -o $(BINARY) $(CPPFLAGS)

re:	fclean all

clean:
	$(RM) $(OBJ) $(TST_OBJ)
	$(RM) *.gcda
	$(RM) *.gcno


fclean: clean
	$(RM) $(BINARY) $(UT_NAME)

.PHONY: all clean fclean tests_run re
