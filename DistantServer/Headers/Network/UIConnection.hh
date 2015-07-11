//
// UIConnection.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 22:53:52 2015 alexis mestag
// Last update Sun Jul 12 00:53:16 2015 alexis mestag
//

#ifndef		__UICONNECTION_HH__
# define	__UICONNECTION_HH__

# include	<memory>
# include	"Entities/User.hh"
# include	"Network/JsonConnection.hh"

class	UIConnection : public JsonConnection
{
private:
  std::shared_ptr<User>		_user;

public:
  explicit UIConnection(boost::asio::ip::tcp::socket socket,
			ConnectionManager &connectionManager);

public:
  virtual void	start() override;

private:
  void		getUser();
  void		forward();
};

#endif
