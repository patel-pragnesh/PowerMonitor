//
// UIHandler.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue May 26 22:30:47 2015 alexis mestag
// Last update Wed May 27 02:49:25 2015 alexis mestag
//

#include		<iostream>
#include		"Network/UIHandler.hh"

UIHandler::UIHandler(boost::asio::io_service &ios,
		     std::string const &address,
		     std::string const &port) :
  _acceptor(ios), _socket(ios),
  _database("powermonitor", "powermonitor", "powermonitor") {

  tcp::resolver	resolver(ios);
  tcp::endpoint	endpoint = *resolver.resolve({address, port});

  _acceptor.open(endpoint.protocol());
  _acceptor.set_option(tcp::acceptor::reuse_address(true));
  _acceptor.bind(endpoint);
  _acceptor.listen();

  this->accept();
}

void	UIHandler::accept() {
  _acceptor.async_accept(_socket, [this](boost::system::error_code const &ec) {
      if (!_acceptor.is_open())
	return ;
      if (!ec) {
	std::cout << "UI connection received" << std::endl;
	_connectionManager.start(std::make_shared<Connection>(std::move(_socket),
							      _connectionManager,
							      _database));
      }
      this->accept();
    });
}

void	UIHandler::stop() {
  std::cout << "UI handler shutting down" << std::endl;
  _acceptor.close();
  _connectionManager.stopAll();
}
