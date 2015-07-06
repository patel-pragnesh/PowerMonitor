//
// MasterModulesHandler.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat May 30 18:44:16 2015 alexis mestag
// Last update Mon Jul  6 21:07:36 2015 alexis mestag
//

#include	<iostream>
#include	<memory>
#include	"Network/MasterModulesHandler.hh"

MasterModulesHandler::MasterModulesHandler(boost::asio::io_service &ios,
					   std::string &&address, std::string &&port) :
  Server("MasterModule handler", ios, std::forward<std::string>(address), std::forward<std::string>(port)),
  _database("powermonitor", "powermonitor", "powermonitor_DistantServer") {
}


Server<Connection>::ConnectionPtr	MasterModulesHandler::getNewConnection() {
  return (this->_getNewConnection<Database &>(_database));
}
