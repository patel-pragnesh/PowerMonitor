//
// JsonConnection.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Jul 11 16:42:56 2015 alexis mestag
// Last update Wed Aug 26 02:04:45 2015 alexis mestag
//

#ifndef		__JSONCONNECTION_HH__
# define	__JSONCONNECTION_HH__

# include	<array>
# include	<json/value.h>
# include	<json/writer.h>
# include	"Network/AbstractConnection.hh"

class		JsonConnection : public AbstractConnection
{
public:
  using	sendHandler		= std::function<void(boost::system::error_code const &error,
						     std::size_t bytes_transferred)>;
  using	recvHandler		= std::function<void(Json::Value const &response)>;

private:
  std::shared_ptr<Json::StreamWriter>	_jsonWriter;
  std::array<char, 8192>		_buffer;
  int					_sizeToRead;

protected:
  JsonConnection() = delete;
  JsonConnection(JsonConnection const &rhs) = delete;
  JsonConnection	&operator=(JsonConnection const &rhs) = delete;

  explicit JsonConnection(boost::asio::ip::tcp::socket socket, ConnectionManager &connectionManager);

public:
  virtual ~JsonConnection() = default;

// protected:
  void		send(Json::Value const &toSend, sendHandler const &handler);
  void		recv(recvHandler const &handler);
};

#endif
