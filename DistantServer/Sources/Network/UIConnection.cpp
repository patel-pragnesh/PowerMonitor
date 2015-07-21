//
// UIConnection.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 23:02:21 2015 alexis mestag
// Last update Tue Jul 21 22:59:00 2015 alexis mestag
//

#include	<iostream>
#include	"Database/UserRepository.hh"
#include	"Network/UIConnection.hh"
#include	"Utils/JsonValidator.hh"

UIConnection::UIConnection(boost::asio::ip::tcp::socket socket,
			   ConnectionManager &connectionManager,
			   Database &database, MasterModulesHandler &mmHandler) :
  JsonConnection(std::move(socket), connectionManager),
  _database(database), _mmHandler(mmHandler) {
}

/*
** Read the request to determine the user
**  - login
**  - already logged, check the session object
** Find the associated master module
** If found, forward the request
** If not, send error
*/

void	UIConnection::start() {
  this->recv([this](Json::Value const &json) {
      if (!_user) {
      	// Find user
      }
      if (_user) {
      	this->forward(json);
      } else {
      	// Error, user not found
      }
    });
}

/*
** Gets the email of the user associated to the connection.
** Gets it from the session object, or from the "email" field
** if it's a login command.
*/
std::string	UIConnection::getEmail(Json::Value const &json) {
  std::string	ret;

  if (json.isMember("session")) { // Not login command
    Json::Value const	&session = json["session"];

    ret = session["email"].asString();
  } else { // Login command
    ret = json["email"].asString();
  }
  if (ret.empty()) {
    std::cerr << "WARNING: email not found" << std::endl;
  }
  return (ret);
}

/*
** Gets the user associated with the email address.
** Only retrieves the user from the database if the user
** is not set or if the email changed.
** Returns true if the user changed (or has just been set),
** false otherwise.
*/
bool	UIConnection::getUser(std::string const &email) {
  bool	retrieveFromDB = true;

  if (_user) {
    retrieveFromDB = _user->getEmail() != email;
  }
  if (retrieveFromDB) {
    UserRepository		ur(_database);
    auto			user = ur.getByEmail(email);

    _user = std::move(user);
  }
  return (retrieveFromDB);
}

/*
**
*/
void	UIConnection::getMasterModuleConnection() {
  _mmConnection = _mmHandler.find([this](MasterModuleConnection const &c) -> bool {
      return (c.getModule()->getUUID() == _user->getModule()->getUUID());
    });
}

void	UIConnection::forward(Json::Value const &json) {
  // _user is set and valid.

  /*
  ** Find the MasterModuleConnection corresponding to the user
  ** Send the json
  */
}
