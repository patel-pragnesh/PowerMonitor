//
// UIConnection.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 22:53:52 2015 alexis mestag
// Last update Tue Jul 21 22:45:57 2015 alexis mestag
//

#ifndef		__UICONNECTION_HH__
# define	__UICONNECTION_HH__

# include	<memory>
# include	"Database/Database.hh"
# include	"Entities/User.hh"
# include	"Network/JsonConnection.hh"
# include	"Network/MasterModulesHandler.hh"

class	UIConnection : public JsonConnection
{
private:
  Database					&_database;
  MasterModulesHandler				&_mmHandler;
  std::shared_ptr<User>				_user;
  std::shared_ptr<MasterModuleConnection>	_mmConnection;

public:
  explicit UIConnection(boost::asio::ip::tcp::socket socket,
			ConnectionManager &connectionManager,
			Database &database, MasterModulesHandler &mmHandler);

public:
  virtual void	start() override;

private:
  void		forward(Json::Value const &json);

  std::string	getEmail(Json::Value const &json);
  bool		getUser(std::string const &email);

  void		getMasterModuleConnection();
};

#endif
