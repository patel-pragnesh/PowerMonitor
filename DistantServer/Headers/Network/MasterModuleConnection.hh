//
// MasterModuleConnection.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 21:10:58 2015 alexis mestag
// Last update Sat Jul 11 19:42:45 2015 alexis mestag
//

#ifndef		__MASTERMODULECONNECTION_H__
# define	__MASTERMODULECONNECTION_H__

# include	"Network/JsonConnection.hh"
# include	"Network/MasterModuleRequestHandler.hh"

class		MasterModuleConnection : public JsonConnection
{
private:
  MasterModuleRequestHandler		_requestHandler;

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
  void			handle(Json::Value const &json);
};

#endif
