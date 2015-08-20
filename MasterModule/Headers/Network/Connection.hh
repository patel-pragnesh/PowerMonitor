//
// Connection.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 28 00:08:12 2015 alexis mestag
// Last update Tue Mar  3 20:38:08 2015 alexis mestag
//

#ifndef			__CONNECTION_HH__
# define		__CONNECTION_HH__

# include		<array>
# include		<memory>
# include		<boost/asio.hpp>
# include		"Network/RequestHandler.hh"
# include		"Utils/Logger.hh"

class			ConnectionManager;

class			Connection : public std::enable_shared_from_this<Connection>
{
private:
  boost::asio::ip::tcp::socket	_socket;
  ConnectionManager		&_connectionManager;
  Logger			_logger;
  RequestHandler		_requestHandler;
  unsigned int			_toRead;
  std::array<char, 8192>	_buffer;
  Json::Value			_request;
  Json::Value			_response;

public:
  Connection() = delete;
  Connection(Connection const &rhs) = delete;

  Connection		&operator=(Connection const &rhs) = delete;

  explicit Connection(boost::asio::ip::tcp::socket socket,
		      ConnectionManager &connectionManager,
		      Database &database);
  ~Connection() = default;

public:
  void			start();
  void			stop();

private:
  void			read();
  void			write();
};

#endif
