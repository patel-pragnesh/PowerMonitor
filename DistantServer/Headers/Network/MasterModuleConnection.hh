//
// MasterModuleConnection.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 21:10:58 2015 alexis mestag
// Last update Wed Aug 26 02:51:05 2015 alexis mestag
//

#ifndef		__MASTERMODULECONNECTION_H__
# define	__MASTERMODULECONNECTION_H__

# include	"Network/JsonConnection.hh"
# include	"Network/MasterModuleRequestHandler.hh"

class		Bridge;

class		MasterModuleConnection : public JsonConnection
{
private:
  Bridge			&_bridge;
  MasterModuleRequestHandler	_requestHandler;

public:
  MasterModuleConnection() = delete;
  MasterModuleConnection(MasterModuleConnection const &rhs) = delete;
  MasterModuleConnection	&operator=(MasterModuleConnection const &rhs) = delete;

  explicit MasterModuleConnection(boost::asio::ip::tcp::socket socket,
				  ConnectionManager &connectionManager,
				  Bridge &bridge, Database &database);

public:
  virtual void	start() override;

  std::shared_ptr<MasterModule>	getModule() const { return (_requestHandler.getModule()); }

  void			forwardSend(Json::Value const &json, sendHandler handler) { this->send(json, handler); }
  void			forwardRecv(recvHandler handler) { this->recv(handler); }
  
private:
  void			handle(Json::Value const &json);
};

#endif
