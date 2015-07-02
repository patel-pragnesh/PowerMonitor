//
// DistantServerConnector.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu May 28 15:01:52 2015 alexis mestag
// Last update Fri Jun 12 02:21:20 2015 alexis mestag
//

#ifndef		__DISTANTSERVERCONNECTOR_HH__
# define	__DISTANTSERVERCONNECTOR_HH__

# include	<map>
# include	<memory>
# include	<string>
# include	<boost/asio.hpp>
# include	<json/value.h>
# include	<json/writer.h>

# include	"Network/AbstractConnection.hh"
# include	"Network/RequestHandler.hh"

using	boost::asio::ip::tcp;

class	DistantServerConnector : public AbstractConnection
{
private:
  using	sendHandler = std::function<void(boost::system::error_code const &error, std::size_t bytes_transferred)>;
  using recvHandler = std::function<void(Json::Value const &json)>;

private:
  boost::asio::io_service		&_ios;
  std::string				_address;
  std::string				_port;
  std::map<std::string, std::shared_ptr<RequestHandler>>	_handlers;

public:
  DistantServerConnector(boost::asio::io_service &ios,
			 std::string const &address,
			 std::string const &port);

private:
  void		connect();
  void		sendUUID();

  void		receiveRequests();
};

#endif
