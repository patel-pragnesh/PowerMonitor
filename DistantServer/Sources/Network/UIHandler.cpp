//
// UIHandler.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Jul  6 18:26:41 2015 alexis mestag
// Last update Thu Jul  9 23:10:10 2015 alexis mestag
//

#include	<iostream>
#include	<memory>
#include	<utility>
#include	"Network/UIHandler.hh"

UIHandler::UIHandler(boost::asio::io_service &ios,
		     std::string &&address, std::string &&port) :
  Server("UIHandler", ios, std::move(address), std::move(port)) {
}

std::shared_ptr<AbstractConnection>	UIHandler::getNewConnection() {
  return (this->_getNewConnection<>());
}
