//
// MasterModuleConnection.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 21:25:46 2015 alexis mestag
// Last update Wed Aug 26 03:03:13 2015 alexis mestag
//

#include	<iostream>
#include	"Network/Bridge.hh"
#include	"Network/MasterModuleConnection.hh"

MasterModuleConnection::MasterModuleConnection(boost::asio::ip::tcp::socket socket,
					       ConnectionManager &connectionManager,
					       Bridge &bridge, Database &database) :
  JsonConnection(std::move(socket), connectionManager),
  _bridge(bridge), _requestHandler(database) {
}

void		MasterModuleConnection::start() {
  // To FIX: should be registered to Bridge only if connect command has already been performed
  _bridge.registerModule(std::dynamic_pointer_cast<MasterModuleConnection>(this->shared_from_this()));
  /*
  ** Pre-Bridge code
  */
  // this->recv([this](Json::Value const &json) {
  //     this->handle(json);
  //   });
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
