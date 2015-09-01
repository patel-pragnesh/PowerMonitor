//
// DistantServerConnector.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu May 28 15:01:52 2015 alexis mestag
// Last update Fri Aug 28 01:30:26 2015 alexis mestag
//

#ifndef		__DISTANTSERVERCONNECTOR_HH__
# define	__DISTANTSERVERCONNECTOR_HH__

# include	<map>
# include	<memory>
# include	<string>
# include	<boost/asio.hpp>
# include	<json/value.h>
# include	<json/writer.h>

# include	"Network/RequestHandler.hh"

class	DistantServerConnector
{
private:
  using	sendHandler = std::function<void(boost::system::error_code const &error, std::size_t bytes_transferred)>;
  using recvHandler = std::function<void(Json::Value const &json)>;
  using	tokenToRequestHandler = std::map<std::string, std::shared_ptr<RequestHandler>>;

private:
  boost::asio::io_service		&_ios;
  boost::asio::ip::tcp::socket		_socket;
  std::string				_address;
  std::string				_port;
  std::shared_ptr<Json::StreamWriter>	_jsonWriter;
  std::array<char, 8192>		_buffer;
  int					_sizeToRead;
  Database				&_database;
  Logger				_logger;
  tokenToRequestHandler			_handlers;

public:
  DistantServerConnector(boost::asio::io_service &ios,
			 std::string const &address,
			 std::string const &port,
			 Database &database);

  void		send(Json::Value const &json, sendHandler f);
  void		recv(recvHandler f);
  
private:
  void		connect();
  void		sendUUID();

  void		receiveRequests();
};

#endif
