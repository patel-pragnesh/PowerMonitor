//
// Connection.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 28 00:08:12 2015 alexis mestag
// Last update Mon Jul  6 21:10:20 2015 alexis mestag
//

#ifndef			__CONNECTION_HH__
# define		__CONNECTION_HH__

# include		<array>
# include		<functional>
# include		<memory>

# include		<boost/asio.hpp>
# include		<json/value.h>
# include		<json/writer.h>

# include		"Network/ConnectionManager.hpp"
# include		"Network/MasterModuleRequestHandler.hh"

class			Connection : public std::enable_shared_from_this<Connection>
{
public:
  using	sendHandler		= std::function<void(boost::system::error_code const &error, std::size_t bytes_transferred)>;
  using	recvHandler		= std::function<void(Json::Value const &response)>;
  using ConnectionManagerType	= ConnectionManager<Connection>;

private:
  boost::asio::ip::tcp::socket		_socket;
  ConnectionManagerType			&_connectionManager;
  MasterModuleRequestHandler		_requestHandler;
  std::shared_ptr<Json::StreamWriter>	_jsonWriter;
  int					_sizeToRead;
  std::array<char, 8192>		_buffer;

public:
  Connection() = delete;
  Connection(Connection const &rhs) = delete;

  Connection		&operator=(Connection const &rhs) = delete;

  explicit Connection(boost::asio::ip::tcp::socket socket,
		      ConnectionManagerType &connectionManager,
		      Database &db);
  ~Connection() = default;

public:
  void			start();
  void			stop();

private:
  void			send(Json::Value const &toSend, sendHandler const &handler);
  void			recv(recvHandler const &handler);

  void			handle(Json::Value const &json);
};

#endif
