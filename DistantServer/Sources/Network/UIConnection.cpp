//
// UIConnection.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 23:02:21 2015 alexis mestag
// Last update Wed Aug 26 03:11:08 2015 alexis mestag
//

#include	<iostream>
#include	"Database/UserRepository.hh"
#include	"Network/Bridge.hh"
#include	"Network/UIConnection.hh"
#include	"Utils/JsonValidator.hh"

UIConnection::UIConnection(boost::asio::ip::tcp::socket socket,
			   ConnectionManager &connectionManager,
			   Bridge &bridge, Database &database, MasterModulesHandler &mmHandler) :
  JsonConnection(std::move(socket), connectionManager),
  _bridge(bridge), _database(database), _mmHandler(mmHandler) {
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
  _bridge.run(std::dynamic_pointer_cast<UIConnection>(this->shared_from_this()));
  /*
  ** Former code when there was no Bridge class
  */
  // this->recv([this](Json::Value const &json) {
  //     std::string	email = this->getEmail(json);
  //     bool		userChanged = this->getUser(email);

  //     if (userChanged) {
  // 	this->getMasterModuleConnection();
  //     }
  //     if (_mmConnection) {
  // 	this->forward(json);
  //     } else {
  // 	// Send error
  //     }
  //   });
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
** Gets the module connection from the Master modules handler and
** the user associated to the received request.
*/
void	UIConnection::getMasterModuleConnection() {
  _mmConnection = _mmHandler.find([this](MasterModuleConnection const &c) -> bool {
      return (c.getModule()->getUUID() == _user->getModule()->getUUID());
    });
}

/*
** Problem when multiple UI working at the same time
** (might send & read packets to & from wrong ends)
*/
void	UIConnection::forward(Json::Value const &json) {
  // Sends the request to the master module
  _mmConnection->forwardSend(json, [this](boost::system::error_code const &error, std::size_t) {
      if (!error) {
	// Reads the response from the master module
	_mmConnection->forwardRecv([this](Json::Value const &json) {
	    // Sends the response to the UI
	    this->send(json, [this](boost::system::error_code const &ec, std::size_t) {
		if (!ec) {
		  this->start();
		} else {
		  // Error while forwarding to UI
		  std::cerr << "Error while forwarding response to UI" << std::endl;
		}
	      });
	  });
      } else {
	// Error while forward sending to master module
	std::cerr << "Error while forward sending to master module" << std::endl;
      }
    });
}
