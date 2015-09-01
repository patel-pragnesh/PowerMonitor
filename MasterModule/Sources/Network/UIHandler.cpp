//
// UIHandler.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue May 26 22:30:47 2015 alexis mestag
// Last update Tue Aug 25 02:09:15 2015 alexis mestag
//

#include		<iostream>
#include		"Network/UIHandler.hh"

UIHandler::UIHandler(boost::asio::io_service &ios,
		     std::string &&address,
		     std::string &&port,
		     Database &db) :
  Server("UIHandler", ios, std::move(address), std::move(port)),
  _db(db) {
}
