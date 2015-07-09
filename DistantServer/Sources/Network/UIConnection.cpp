//
// UIConnection.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 23:02:21 2015 alexis mestag
// Last update Thu Jul  9 23:04:50 2015 alexis mestag
//

#include	"Network/UIConnection.hh"

UIConnection::UIConnection(boost::asio::ip::tcp::socket socket,
			   ConnectionManager &connectionManager) :
  AbstractConnection(std::move(socket), connectionManager) {
}

void	UIConnection::start() {
  
}
