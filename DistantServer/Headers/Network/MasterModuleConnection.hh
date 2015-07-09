//
// MasterModuleConnection.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 21:10:58 2015 alexis mestag
// Last update Thu Jul  9 22:49:38 2015 alexis mestag
//

#ifndef		__MASTERMODULECONNECTION_H__
# define	__MASTERMODULECONNECTION_H__

# include	<array>
# include	<json/value.h>
# include	<json/writer.h>
# include	"Network/AbstractConnection.hh"
# include	"Network/ConnectionManager.hh"
# include	"Network/MasterModuleRequestHandler.hh"

class		MasterModuleConnection : public AbstractConnection
{
public:
  using	sendHandler		= std::function<void(boost::system::error_code const &error,
						     std::size_t bytes_transferred)>;
  using	recvHandler		= std::function<void(Json::Value const &response)>;

private:
  MasterModuleRequestHandler		_requestHandler;
  std::shared_ptr<Json::StreamWriter>	_jsonWriter;
  std::array<char, 8192>		_buffer;
  int					_sizeToRead;

public:
  MasterModuleConnection() = delete;
  MasterModuleConnection(MasterModuleConnection const &rhs) = delete;
  MasterModuleConnection	&operator=(MasterModuleConnection const &rhs) = delete;

  explicit MasterModuleConnection(boost::asio::ip::tcp::socket socket,
				  ConnectionManager &connectionManager,
				  Database &database);

public:
  virtual void	start() override;

private:
  void			send(Json::Value const &toSend, sendHandler const &handler);
  void			recv(recvHandler const &handler);

  void			handle(Json::Value const &json);
};

#endif
