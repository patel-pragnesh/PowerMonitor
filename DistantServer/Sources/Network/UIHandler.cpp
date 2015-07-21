//
// UIHandler.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Jul  6 18:26:41 2015 alexis mestag
// Last update Tue Jul 21 22:44:12 2015 alexis mestag
//

#include	<iostream>
#include	<memory>
#include	<utility>
#include	"Network/UIHandler.hh"

UIHandler::UIHandler(boost::asio::io_service &ios,
		     std::string &&address, std::string &&port,
		     Database &db, MasterModulesHandler &mmHandler) :
  Server("UIHandler", ios, std::move(address), std::move(port)),
  _database(db), _mmHandler(mmHandler) {
}

std::shared_ptr<AbstractConnection>	UIHandler::getNewConnection() {
  return (this->_getNewConnection<Database &, MasterModulesHandler &>(_database, _mmHandler));
}
