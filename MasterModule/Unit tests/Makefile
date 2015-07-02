##
## Makefile for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
## 
## Made by alexis mestag
## Login   <mestag_a@epitech.net>
## 
## Started on  Sat Nov 29 00:07:36 2014 alexis mestag
## Last update Wed Apr 29 22:17:29 2015 alexis mestag
##

NAME=		unit_tests

SRC_DIR=	Sources
SRC=		main.cpp			\
		Logger.cpp			\
		Tests/AlertTest.cpp		\
		Tests/LoginTest.cpp		\
		Tests/TimeSlotTest.cpp		\
		UnitTest.cpp			\
		UnitTestsClient.cpp

PARENT_DIR=	..
PARENT_SRC=	Utils/JsonValidator.cpp
PARENT_SRC:=	$(addprefix $(PARENT_DIR)/$(SRC_DIR)/, $(PARENT_SRC))

SRC:=		$(addprefix $(SRC_DIR)/, $(SRC))
SRC+=		$(PARENT_SRC)

OBJ=		$(SRC:.cpp=.o)

HDR_DIR=	Headers

INCLUDEFLAGS=	-I $(HDR_DIR)
INCLUDEFLAGS+=	-I $(PARENT_DIR)/$(HDR_DIR)

OBJ:=		$(OBJ)

CPPFLAGS=	-W -Wall -Wextra -std=c++11 $(INCLUDEFLAGS) -g
LDFLAGS=	-L/usr/lib/odb
LDFLAGS+=	-lodb -lodb-mysql -lboost_system -lpthread -ljsoncpp -lcryptopp
CXX=		g++

##
# Rules
##

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
