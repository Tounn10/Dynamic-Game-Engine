##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

CC			= g++

CPPFLAGS	=	-Wall -Wextra -std=c++20 -fPIC -fno-gnu-unique
CPPFLAGS	+=	-iquote include -iquote ../Common/include -iquote ../../Common/include

SRC			=	src/entryPoint.cpp	\
				src/ArcadeSdl2.cpp	\
				src/SDLTexture.cpp	\
				src/SDLFont.cpp		\
				../../Common/src/AEvent.cpp	\

OBJ			=	$(SRC:.cpp=.o)

BINARY		=	arcade_sdl2.so

all: $(BINARY)

$(BINARY): $(OBJ)
	$(CC) -shared $(OBJ) -o $(BINARY) $(CPPFLAGS) $(LDLIBS) -lSDL2 -lSDL2_ttf -lSDL2_image

re:	fclean all

clean:
	$(RM) $(OBJ) $(TST_OBJ)
	$(RM) *.gcda
	$(RM) *.gcno


fclean: clean
	$(RM) $(BINARY) $(UT_NAME)

.PHONY: all clean fclean tests_run re