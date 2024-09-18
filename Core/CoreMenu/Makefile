##
## EPITECH PROJECT, 2024
## arcade
## File description:
## Makefile
##

CC			= g++

CPPFLAGS	=	-Wall -Wextra -std=c++20 -fPIC -fno-gnu-unique
CPPFLAGS	+=	-iquote include -iquote ../Common/include -iquote ../../Common/include

SRC			=	src/CoreMenu.cpp	\
				src/CoreLibManager.cpp	\
				src/DirectoryLister/IDirectoryLister.cpp	\
				src/DirectoryLister/SafeDirectoryLister.cpp	\
				../../Common/src/AObject.cpp

OBJ			=	$(SRC:.cpp=.o)

BINARY		=	arcade_menu.so

all: $(BINARY)

$(BINARY): $(OBJ)
	$(CC) -shared $(OBJ) -o $(BINARY) $(CPPFLAGS)
	mv $(BINARY) ../../

re:	fclean all

clean:
	$(RM) $(OBJ) $(TST_OBJ)
	$(RM) *.gcda
	$(RM) *.gcno


fclean: clean
	$(RM) $(BINARY) $(UT_NAME)

.PHONY: all clean fclean tests_run re
