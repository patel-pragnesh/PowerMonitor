//
// MasterModuleServer.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Jan 24 18:51:56 2015 alexis mestag
// Last update Mon Feb 23 00:59:16 2015 alexis mestag
//

#include		<iostream>
#include		<boost/bind.hpp>
#include		"Network/MasterModuleServer.hh"

MasterModuleServer::MasterModuleServer(std::string const &address, std::string const &port) :
  _ios(), _signals(_ios), _acceptor(_ios), _socket(_ios),
  _database("powermonitor", "powermonitor", "powermonitor"),
  _connectionManager() {

  _signals.add(SIGINT);
  _signals.add(SIGTERM);
  _signals.add(SIGQUIT);
  this->handleSignals();

  tcp::resolver		resolver(_ios);
  tcp::endpoint		endpoint = *resolver.resolve({address, port});

  _acceptor.open(endpoint.protocol());
  _acceptor.set_option(tcp::acceptor::reuse_address(true));
  _acceptor.bind(endpoint);
  _acceptor.listen();

  this->handleAccept();
}

void			MasterModuleServer::run() {
  _ios.run();
}

void			MasterModuleServer::handleSignals() {
  _signals.async_wait([this](boost::system::error_code const &, int) {
      std::cout << "Shutting down" << std::endl;
      _acceptor.close();
      _connectionManager.stopAll();
    });
}

void			MasterModuleServer::handleAccept() {
  _acceptor.async_accept(_socket, [this](boost::system::error_code const &ec) {
      if (!_acceptor.is_open())
	return ;
      if (!ec) {
	std::cout << "New connection received" << std::endl;
	_connectionManager.start(std::make_shared<Connection>(std::move(_socket),
							      _connectionManager,
							      _database));
      }
      this->handleAccept();
    });
}
