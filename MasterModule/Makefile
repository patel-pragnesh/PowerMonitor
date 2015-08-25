##
## Makefile for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
## 
## Made by alexis mestag
## Login   <mestag_a@epitech.net>
## 
## Started on  Sat Nov 29 00:07:36 2014 alexis mestag
## Last update Tue Aug 25 02:06:35 2015 alexis mestag
##

NAME=		master
ODB_SCHEMA=	odb_schema.sql

SRC_DIR=	Sources
SRC=		main.cpp				\
		Database/Database.cpp			\
		Database/AlertRepository.cpp		\
		Database/DefaultProfileRepository.cpp	\
		Database/ReadingRepository.cpp		\
		Database/SessionRepository.cpp		\
		Database/TimeSlotRepository.cpp		\
		Database/UserRepository.cpp		\
		Entities/Alert.cpp			\
		Entities/DefaultProfile.cpp		\
		Entities/Entity.cpp			\
		Entities/Information.cpp		\
		Entities/InternalProfile.cpp		\
		Entities/Profile.cpp			\
		Entities/Reading.cpp			\
		Entities/Session.cpp			\
		Entities/SlaveModule.cpp		\
		Entities/TimeSlot.cpp			\
		Entities/Unit.cpp			\
		Entities/User.cpp			\
		Entities/Week.cpp			\
		Network/AbstractConnection.cpp		\
		Network/ConnectionManager.cpp		\
		Network/JsonConnection.cpp		\
		Network/RequestHandler.cpp		\
		Network/UIConnection.cpp		\
		Network/UIHandler.cpp			\
		Utils/JsonValidator.cpp			\
		Utils/Logger.cpp			\
		Utils/Time.cpp
SRC:=		$(addprefix $(SRC_DIR)/, $(SRC))

OBJ=		$(SRC:.cpp=.o)

HDR_DIR=	Headers

##
# ODB specific variables
##

ODB=			odb
ODB_FILE_SUFFIX=	-odb
ODB_SQL_FILE_SUFFIX=	
ODB_HXX_SUFFIX=		.hxx
ODB_IXX_SUFFIX=		.ixx
ODB_CXX_SUFFIX=		.cpp
ODB_SQL_SUFFIX=		.sql
ODB_CXX_FILE_PATTERN=	$(ODB_FILE_SUFFIX)$(ODB_CXX_SUFFIX)
ODB_HXX_FILE_PATTERN=	$(ODB_FILE_SUFFIX)$(ODB_HXX_SUFFIX)
ODB_IXX_FILE_PATTERN=	$(ODB_FILE_SUFFIX)$(ODB_IXX_SUFFIX)
ODB_SQL_FILE_PATTERN=	$(ODB_SQL_FILE_SUFFIX)$(ODB_SQL_SUFFIX)

ODB_HDR=	Entities/Alert.hh			\
		Entities/DefaultProfile.hh		\
		Entities/Entity.hh			\
		Entities/Information.hh			\
		Entities/InternalProfile.hh		\
		Entities/Profile.hh			\
		Entities/Reading.hh			\
		Entities/Session.hh			\
		Entities/SlaveModule.hh			\
		Entities/TimeSlot.hh			\
		Entities/Unit.hh			\
		Entities/User.hh			\
		Entities/Week.hh			\
		Entities/Views/SlaveModuleCount.hh	\
		Entities/Views/GlobalReading.hh		\
		Utils/Time.hh
ODB_HDR:=	$(addprefix $(HDR_DIR)/, $(ODB_HDR))
ODB_CXX=	$(ODB_HDR:.hh=$(ODB_CXX_FILE_PATTERN))
ODB_HXX=	$(ODB_HDR:.hh=$(ODB_HXX_FILE_PATTERN))
ODB_IXX=	$(ODB_HDR:.hh=$(ODB_IXX_FILE_PATTERN))
ODB_SQL=	$(ODB_HDR:.hh=$(ODB_SQL_FILE_PATTERN))
ODB_GEN=	$(ODB_CXX) $(ODB_HXX) $(ODB_IXX) $(ODB_SQL)

INCLUDEFLAGS=	-I $(HDR_DIR)

%$(ODB_CXX_FILE_PATTERN) %$(ODB_HXX_FILE_PATTERN) %$(ODB_IXX_FILE_PATTERN) %$(ODB_SQL_FILE_PATTERN) : %.hh
		$(ODB) -d mysql -q -s -e --std c++11 --default-pointer 'std::shared_ptr' --cxx-suffix $(ODB_CXX_SUFFIX) $(INCLUDEFLAGS) -o $(<D) $<

ODB_OBJ=	$(ODB_CXX:$(ODB_CXX_SUFFIX)=.o)
OBJ:=		$(ODB_OBJ) $(OBJ)

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

$(OBJ):		$(ODB_HXX)

$(ODB_GEN):

$(ODB_SCHEMA):	$(ODB_HDR)
		$(ODB)  -d mysql -q --generate-schema-only --std c++11 --at-once $(INCLUDEFLAGS) --input-name $(ODB_SCHEMA) -o SQL $(ODB_HDR)

TESTS_SRC=	Tests/test.cpp
TESTS_OBJ=	$(TESTS_SRC:.cpp=.o)
TESTS=		$(basename $(TESTS_SRC))
OBJ_NOMAIN=	$(filter-out Sources/main.o, $(OBJ))

%:	%.cpp
	g++  $(CPPFLAGS)  -c -o $@.o $<
	g++ -o $@ $@.o $(OBJ_NOMAIN) $(LDFLAGS)

tests:	$(TESTS)

$(TESTS):	$(OBJ_NOMAIN)

clean:
		$(RM) $(OBJ)
		$(RM) $(TESTS_OBJ)

fclean:		clean
		$(RM) $(NAME)
		$(RM) $(ODB_GEN)
		$(RM) $(ODB_SCHEMA)
		$(RM) $(TESTS)

re:		fclean all
