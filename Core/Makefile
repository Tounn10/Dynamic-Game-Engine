##
## EPITECH PROJECT, 2024
## B-OOP-400-BAR-4-1-tekspice-ambroise.jacquemet-ramirez-vega
## File description:
## Makefile
##

CC			= g++

CPPFLAGS	=	-Wall -Wextra -std=c++20 -fPIC -fno-gnu-unique
CPPFLAGS	+=	-iquote include -iquote ../Common/include -iquote CoreMenu/include

SRC			=	src/main.cpp	\
				src/Core/Core.cpp	\
				src/Core/Loader/DLLoader.cpp	\
				../Common/src/AObject.cpp	\
				../Common/src/AEvent.cpp	\



OBJ			=	$(SRC:.cpp=.o)

BINARY		=	arcade

all: $(BINARY)

$(BINARY): $(OBJ)
	make -C CoreMenu
	$(CC) $(OBJ) -o $(BINARY) $(CPPFLAGS) $(LDLIBS)

re:	fclean all

clean:
	make -C CoreMenu clean
	$(RM) $(OBJ) $(TST_OBJ)
	$(RM) *.gcda
	$(RM) *.gcno


fclean: clean
	make -C CoreMenu fclean
	$(RM) $(BINARY) $(UT_NAME)

.PHONY: all clean fclean tests_run re