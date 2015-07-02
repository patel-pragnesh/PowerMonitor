//
// MasterModulesHandler.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat May 30 18:44:16 2015 alexis mestag
// Last update Wed Jun 10 08:32:51 2015 laurent ansel
//

#include	<iostream>
#include	<memory>
#include	"Network/MasterModulesHandler.hh"

MasterModulesHandler::MasterModulesHandler(boost::asio::io_service &ios,
					   std::string const &address,
					   std::string const &port) :
  _ios(ios), _acceptor(_ios), _socket(_ios),
  _database("powermonitor", "powermonitor", "powermonitor_DistantServer")
{
  tcp::resolver		resolver(_ios);
  tcp::endpoint		endpoint = *resolver.resolve({address, port});

  _acceptor.open(endpoint.protocol());
  _acceptor.set_option(tcp::acceptor::reuse_address(true));
  _acceptor.bind(endpoint);
  _acceptor.listen();

  this->accept();
}

void		MasterModulesHandler::stop()
{
  std::cout << "MasterModules handler shutting down" << std::endl;
  _acceptor.close();
  _connectionManager.stop();
}

void		MasterModulesHandler::accept() {
  _acceptor.async_accept(_socket, [this](boost::system::error_code const &ec) {
      if (!_acceptor.is_open())
	return ;
      if (!ec) {
	std::cout << "MasterModule connection received" << std::endl;
	_connectionManager.start(std::make_shared<Connection>(std::move(_socket),
							      _connectionManager,
							      _database));
      }
      this->accept();
    });
}
