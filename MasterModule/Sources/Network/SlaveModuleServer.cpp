//
// SlaveModuleServer.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Aug 25 02:30:34 2015 alexis mestag
// Last update Tue Aug 25 03:08:35 2015 alexis mestag
//

#include	"Network/SlaveModuleServer.hh"

SlaveModuleServer::SlaveModuleServer(boost::asio::io_service &ios,
				     std::string &&address, std::string &&port,
				     Database &db) :
  Server("SlaveModuleServer", ios, std::move(address), std::move(port)),
  _db(db) {
}
