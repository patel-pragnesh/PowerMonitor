//
// AbstractConnection.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 21:20:51 2015 alexis mestag
// Last update Thu Jul  9 22:15:41 2015 alexis mestag
//

#include	"Network/AbstractConnection.hh"

AbstractConnection::AbstractConnection(boost::asio::ip::tcp::socket socket,
				       ConnectionManager &connectionManager) :
  _socket(std::move(socket)), _connectionManager(connectionManager) {
}

void		AbstractConnection::stop() {
  _socket.close();
}
