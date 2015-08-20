//
// MasterModuleConnection.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 21:25:46 2015 alexis mestag
// Last update Sat Jul 11 19:55:25 2015 alexis mestag
//

#include	<iostream>
#include	"Network/MasterModuleConnection.hh"

MasterModuleConnection::MasterModuleConnection(boost::asio::ip::tcp::socket socket,
					       ConnectionManager &connectionManager,
					       Database &database) :
  JsonConnection(std::move(socket), connectionManager),
  _requestHandler(database) {
}

void		MasterModuleConnection::start() {
  this->recv([this](Json::Value const &json) {
      this->handle(json);
    });
}

void			MasterModuleConnection::handle(Json::Value const &json) {
  Json::Value		response;

  std::cout << "Received: " << json.toStyledString();
  _requestHandler(json, response);
  this->send(response, [this](boost::system::error_code const &ec, std::size_t) {
      if (!ec) {
	this->start();
      }
    });
}
