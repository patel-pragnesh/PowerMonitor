//
// UIHandler.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Jul  6 18:26:41 2015 alexis mestag
// Last update Mon Jul  6 18:36:26 2015 alexis mestag
//

#include	<iostream>
#include	<memory>
#include	<utility>
#include	"Network/UIHandler.hh"

UIHandler::UIHandler(boost::asio::io_service &ios,
		     std::string &&address,
		     std::string &&port) :
  _ios(ios), _acceptor(_ios), _socket(_ios) {
  tcp::resolver		resolver(_ios);
  tcp::endpoint		endpoint = *resolver.resolver({std::forward(address), std::forward(port)});

  _acceptor.open(endpoint.protocol());
  _acceptor.set_option(tcp::acceptor::reuse_address(true));
  _acceptor.bind(endpoint);
  _acceptor.listen();

  this->accept();
}

void		UIHandler::stop() {
  std::cout << "UIHandler shutting down" << std::endl;
  _acceptor.close();
}

void		UIHandler::accept() {
  _acceptor.async_accept(_socket, [this](boost::system::error_code const &ec) {
      if (!_acceptor.is_open())
	return ;
      if (!ec) {
	std::cout << "UI connection received" << std::endl;
      }
      this->accept();
    });
}
