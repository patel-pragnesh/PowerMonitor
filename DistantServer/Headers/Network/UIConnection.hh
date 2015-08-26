//
// UIConnection.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 22:53:52 2015 alexis mestag
// Last update Wed Aug 26 03:12:50 2015 alexis mestag
//

#ifndef		__UICONNECTION_HH__
# define	__UICONNECTION_HH__

# include	<memory>
# include	"Database/Database.hh"
# include	"Entities/User.hh"
# include	"Network/JsonConnection.hh"
# include	"Network/MasterModulesHandler.hh"

class	Bridge;

class	UIConnection : public JsonConnection
{
private:
  Bridge					&_bridge;
  Database					&_database;
  MasterModulesHandler				&_mmHandler;
  std::shared_ptr<User>				_user;
  std::shared_ptr<MasterModuleConnection>	_mmConnection;

public:
  explicit UIConnection(boost::asio::ip::tcp::socket socket,
			ConnectionManager &connectionManager,
			Bridge &bridge, Database &database, MasterModulesHandler &mmHandler);

public:
  virtual void	start() override;

  std::shared_ptr<User>	getUser() const { return (_user); }
  void			searchUser(Json::Value const &json) { this->getUser(this->getEmail(json)); }
  
// private:
  void		forward(Json::Value const &json);

  std::string	getEmail(Json::Value const &json);
  bool		getUser(std::string const &email);

  void		getMasterModuleConnection();
};

#endif
