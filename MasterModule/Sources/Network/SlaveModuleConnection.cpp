//
// SlaveModuleConnection.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Aug 25 02:37:13 2015 alexis mestag
// Last update Tue Aug 25 03:08:03 2015 alexis mestag
//

#include	"Network/SlaveModuleConnection.hh"

SlaveModuleConnection::SlaveModuleConnection(boost::asio::ip::tcp::socket socket,
					     ConnectionManager &connectionManager,
					     Database &db) :
  AbstractConnection(std::move(socket), connectionManager),
  _db(db) {
}
