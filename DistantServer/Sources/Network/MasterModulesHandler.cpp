//
// MasterModulesHandler.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat May 30 18:44:16 2015 alexis mestag
// Last update Wed Aug 26 02:43:58 2015 alexis mestag
//

#include	<iostream>
#include	<memory>
#include	"Network/MasterModulesHandler.hh"

MasterModulesHandler::MasterModulesHandler(boost::asio::io_service &ios,
					   std::string &&address, std::string &&port,
					   Bridge &bridge, Database &db) :
  Server("MasterModule handler", ios, std::move(address), std::move(port)),
  _bridge(bridge), _database(db) {
}


std::shared_ptr<AbstractConnection>	MasterModulesHandler::getNewConnection() {
  return (this->_getNewConnection<Bridge &, Database &>(_bridge, _database));
}
