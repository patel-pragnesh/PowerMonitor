//
// UIConnection.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 23:02:21 2015 alexis mestag
// Last update Sun Jul 12 00:57:06 2015 alexis mestag
//

#include	"Network/UIConnection.hh"
#include	"Utils/JsonValidator.hh"

UIConnection::UIConnection(boost::asio::ip::tcp::socket socket,
			   ConnectionManager &connectionManager) :
  JsonConnection(std::move(socket), connectionManager) {
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
  if (!_user) {
    this->getUser();
  }
}

void	UIConnection::getUser() {
  this->recv([this](Json::Value const &json) {
      // If no session, then login command
      // If session, then, get user by token
      std::string const		cmd = json["cmd"].asString();
    });
}
