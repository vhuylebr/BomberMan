##
## EPITECH PROJECT, 2018
## Indie Studio
## File description:
## Makefile
##

SRC		= 	src/

GAME	=	Game/

IRR	=	Irrlicht/

SRCS	=	$(SRC)Menu.cpp	\
		$(SRC)MenuItem.cpp	\
		$(SRC)main.cpp	\
		$(SRC)Core.cpp	\
		$(SRC)Actions.cpp	\
		$(GAME)GameCore.cpp\
		$(IRR)IrrLib.cpp\
		$(IRR)MyEventReceiver.cpp	\
		$(GAME)Wall.cpp	\
		$(GAME)Crate.cpp	
		#$(GAME)Item.cpp	
		#$(GAME)eItem.cpp	
		#$(GAME)Bomb.cpp	
		#$(GAME)Box.cpp	
		#$(GAME)Player.cpp

CPPFLAGS	+= -I./include -Wall -std=gnu++1z -I/usr/include/irrlicht/ -lIrrlicht -lGL -LGLU

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
