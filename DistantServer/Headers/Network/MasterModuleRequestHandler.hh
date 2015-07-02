//
// MasterModuleRequestHandler.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat May 30 22:28:29 2015 alexis mestag
// Last update Wed Jun 10 08:18:46 2015 laurent ansel
//

#ifndef		__MASTERMODULEREQUESTHANDLER_HH__
# define	__MASTERMODULEREQUESTHANDLER_HH__

# include	"Database/Database.hh"

# include	<json/value.h>

class		Entity;
class		Connection;

class		MasterModuleRequestHandler
{
public:
  enum		eReturnCode
    {
      Ok					= 0,
      Generic_NotWellFormattedRequest		= 0x101,
      Generic_CommandNotFound			= 0x102,
      Generic_UserAlreadyExist			= 0x201,
      Generic_MasterModuleAlreadyConnected	= 0x202,
      Generic_UserUnknown			= 0x203
    };

private:
  static std::string const	returnCodeKey;
  static std::string const	returnCodeStringKey;

private:
  Database	&_database;
  Connection	&_network;
  Entity	*_owner;

public:
  MasterModuleRequestHandler(Database &db, Connection &network);
  ~MasterModuleRequestHandler() = default;

public:
  bool		operator()(Json::Value const &request, Json::Value &response);

private:
  bool		commandHandler(Json::Value const &request, Json::Value &response);
  bool		connect(Json::Value const &request, Json::Value &response);
  bool		addUser(Json::Value const &request, Json::Value &response);
  bool		login(Json::Value const &request, Json::Value &response);

private:
  void		returnCode(Json::Value &response, eReturnCode const &code);
};

# include	"Network/Connection.hh"
# include	"Entities/Entity.hh"

#endif
