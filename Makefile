##
## EPITECH PROJECT, 2018
## Indie Studio
## File description:
## Makefile
##

SRC		= 	src/

GAME	=	Game/

SRCS	=	$(SRC)Menu.cpp	\
		$(SRC)MenuItem.cpp	\
		$(GAME)Bomb.cpp	\
		$(GAME)Box.cpp	\
		$(GAME)Item.cpp	\
		$(GAME)Player.cpp\
		$(GAME)Wall.cpp	\

CPPFLAGS	+= -I./include -Wall -Wextra -std=gnu++1z -I/usr/include/irrlicht/ -lIrrlicht -lGL -LGLU

CC	=	g++

RM	=	rm -f

OBJS	=	$(SRCS:.cpp=.o)

NAME	=	bomberman

all: $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(CPPFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
