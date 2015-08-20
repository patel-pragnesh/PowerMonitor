//
// AbstractConnection.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jun 12 01:50:49 2015 alexis mestag
// Last update Fri Jun 12 02:15:23 2015 alexis mestag
//

#ifndef		__ABSTRACTCONNECTION_HH__
# define	__ABSTRACTCONNECTION_HH__

# include	<array>
# include	<memory>
# include	<boost/asio.hpp>
# include	<json/writer.h>

using	boost::asio::ip::tcp;

class	AbstractConnection
{
private:
  using	sendHandler	= std::function<void(boost::system::error_code const &error, std::size_t bytes_transferred)>;
  using recvHandler	= std::function<void(Json::Value const &json)>;
  using connectHandler	= std::function<void(boost::system::error_code const &error, tcp::resolver::iterator it)>;

private:
  tcp::socket				_socket;
  std::unique_ptr<Json::StreamWriter>	_jsonWriter;
  unsigned int				_sizeToRead;
  std::array<char, 8192>		_buffer;
  
protected:
  AbstractConnection(boost::asio::io_service &ios);
  AbstractConnection(tcp::socket &&socket);

private:
  void	init();

public:
  virtual ~AbstractConnection() = default;

protected:
  void	connect(tcp::resolver::iterator endpoint_it, connectHandler const &handler);
  void	send(Json::Value const &json, sendHandler const &handler);
  void	recv(recvHandler const &handler);
};

#endif
