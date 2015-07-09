//
// MasterModuleRequestHandler.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat May 30 22:33:34 2015 alexis mestag
// Last update Thu Jul  9 22:36:05 2015 alexis mestag
//

#include	<iostream>
#include	<memory>
#include	<sstream>

#include	"Database/MasterModuleRepository.hh"
#include	"Database/UserRepository.hh"
#include	"Network/MasterModuleRequestHandler.hh"
#include	"Utils/JsonValidator.hh"

MasterModuleRequestHandler::MasterModuleRequestHandler(Database &db/*, Connection &network*/)
  : _database(db)/*,
    _network(network),
    _owner(NULL)*/
{
}

bool		MasterModuleRequestHandler::operator()(Json::Value const &request, Json::Value &response) {
  static JsonValidator	requestValidator = {{"cmd", &JsonValidator::isNonEmptyString}};
  bool			ret = requestValidator(request);

  response.clear();
  if (ret) {
    ret = this->commandHandler(request, response);
  }
  if (ret) {
    this->returnCode(response, Ok);
  }
  return (ret);
}

typedef std::pair<bool (MasterModuleRequestHandler::*)(Json::Value const &, Json::Value &),
		  JsonValidator>	handler_validator;
typedef std::map<std::string,
		 handler_validator>	map_to_handler_validator;

bool		MasterModuleRequestHandler::commandHandler(Json::Value const &request, Json::Value &response) {
  static map_to_handler_validator	router =
    {
      {"connect",
       {
	 &MasterModuleRequestHandler::connect,
	 {
	   {"id", &Json::Value::isUInt64}
	 }
       }
      },
      {"addUser",
       {
	 &MasterModuleRequestHandler::addUser,
	 {
	   {"email", &JsonValidator::isNonEmptyString}
	 }
       }
      },
      {"login",
       {
	 &MasterModuleRequestHandler::login,
	 {
	   {"email", &JsonValidator::isNonEmptyString}
	 }
       }
      }
    };
  std::string					cmd = request["cmd"].asString();
  map_to_handler_validator::const_iterator	it = router.find(cmd);
  bool						ret = it != router.end();

  if (ret) {
    std::unique_ptr<Database::transaction_type>	t(_database.getTransaction());

    try {
      ret = (this->*it->second.first)(request, response);
      t->commit();
    } catch (odb::exception const &e) {
      std::cerr << "ODB Exception: " << e.what() << std::endl;
      t->rollback();
    }
  }
  return (ret);
}

bool		MasterModuleRequestHandler::connect(Json::Value const &request, Json::Value &response) {
  MasterModuleRepository			mmr(_database);
  Repository<MasterModule>::pointer_type	module = mmr.getByUUID(request["id"].asString());
  bool						ret = true;

  if (module)
    {
      // if (module->isConnect())
      // 	{
      // 	  //_logger.err() << "MasterModule already connected" << std::endl;
      // 	  this->returnCode(response, Generic_MasterModuleAlreadyConnected);
      // 	}
      // else
      // 	{
      // 	  // module->setNetwork(&_network);
      // 	  //send response
      // 	}
    }
  else
    {
      // Add this module to the database

      std::string				uuid = request["id"].asString();
      MasterModule				*master = new MasterModule(uuid/*, &_network*/);

      mmr.persist(*master);
      //_owner = master;
      //send response
    }
  return (ret);
}

bool		MasterModuleRequestHandler::addUser(Json::Value const &request, Json::Value &response) {
  UserRepository			r(_database);
  Repository<User>::pointer_type	user = r.getByEmail(request["email"].asString());
  bool					ret = false;

  if (user)
    {
      //_logger.err() << "User already exist" << std::endl;
      this->returnCode(response, Generic_UserAlreadyExist);
    }
  else
    {
      std::string			email = request["email"].asString();
      User				*u = new User(email/*, &_network*/);

      // if (_owner)
      // 	u->setModule(std::shared_ptr<MasterModule>(dynamic_cast<MasterModule *>(_owner)));
      r.persist(*u);
    }
  return (ret);
}

bool		MasterModuleRequestHandler::login(Json::Value const &request, Json::Value &response)
{
  UserRepository			r(_database);
  Repository<User>::pointer_type	user = r.getByEmail(request["email"].asString());
  bool					ret = false;

  if (user)
    {
      // user->setNetwork(&_network);
      // _owner = reinterpret_cast<User *>(&user);
    }
  else
    {
      //_logger.err() << "User unknown" << std::endl;
      this->returnCode(response, Generic_UserUnknown);
    }
  return (ret);
}


std::string const	MasterModuleRequestHandler::returnCodeKey = "returnCode";
std::string const	MasterModuleRequestHandler::returnCodeStringKey = "returnCodeString";

void		MasterModuleRequestHandler::returnCode(Json::Value &response, eReturnCode const &code) {
  std::ostringstream	oss;

  response[returnCodeKey] = code;
  oss << std::hex << std::showbase << code;
  response[returnCodeStringKey] = oss.str();
}
