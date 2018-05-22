##
## EPITECH PROJECT, 2018
## Indie Studio
## File description:
## Makefile
##

CXX	=	g++ -g3

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
		$(GAME)Crate.cpp	\
		$(GAME)Player.cpp	\
		$(GAME)Bomb.cpp	\
		$(GAME)ACube.cpp	
		#$(GAME)Item.cpp	
		#$(GAME)eItem.cpp	

CXXFLAGS	= -I./include -Wall -std=gnu++1z -I/usr/include/irrlicht/ -lIrrlicht -lsfml-graphics -lsfml-window -lsfml-system -lsfml-system -lsfml-window -lsfml-network -lsfml-graphics -lsfml-audio

RM	=	rm -f

OBJS	=	$(SRCS:.cpp=.o)

NAME	=	bomberman

all: $(NAME)

$(NAME):	$(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(CXXFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
