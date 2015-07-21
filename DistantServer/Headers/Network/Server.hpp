//
// Server.hpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Jul  6 19:35:55 2015 alexis mestag
// Last update Tue Jul 21 19:34:48 2015 alexis mestag
//

#ifndef		__SERVER_HPP__
# define	__SERVER_HPP__

# include	<iostream>
# include	<memory>
# include	<string>
# include	<type_traits>
# include	<utility>
# include	<boost/asio.hpp>

# include	"Network/AbstractConnection.hh"
# include	"Network/ConnectionManager.hh"

using	boost::asio::ip::tcp;

template<typename C>
class		Server
{
  static_assert(std::is_base_of<AbstractConnection, C>::value,
		"Template C must be a derived class of AbstractConnection");

private:
  std::string			_name;
  boost::asio::io_service	&_ios;
  tcp::acceptor			_acceptor;
  tcp::socket			_socket;
  ConnectionManager		_connectionManager;
  
public:
  Server(std::string &&name, boost::asio::io_service &ios,
	 std::string &&address, std::string &&port) :
    _name(std::forward<std::string>(name)), _ios(ios),
    _acceptor(_ios), _socket(_ios) {
    tcp::resolver	resolver(_ios);
    tcp::endpoint	endpoint = *resolver.resolve({std::forward<std::string>(address), std::forward<std::string>(port)});

    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(tcp::acceptor::reuse_address(true));
    _acceptor.bind(endpoint);
    _acceptor.listen();

    this->accept();
  }

  void		stop() {
    std::cout << _name << ": shutting down" << std::endl;
    _acceptor.close();
    _connectionManager.stop();
  }

protected:
  template<typename... Args>
  std::shared_ptr<C>	_getNewConnection(Args... params) {
    return (std::make_shared<C>(std::move(_socket), _connectionManager, params...));
  }

public:
  virtual std::shared_ptr<AbstractConnection>	getNewConnection() = 0;

private:
  void		accept() {
    _acceptor.async_accept(_socket, [this](boost::system::error_code const &ec) {
	if (!_acceptor.is_open())
	  return ;
	if (!ec) {
	  std::cout << _name << ": connection received" << std::endl;
	  _connectionManager.start(this->getNewConnection());
	}
	this->accept();
      });
  }
};

#endif
