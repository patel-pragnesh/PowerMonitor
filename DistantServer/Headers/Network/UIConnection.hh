//
// UIConnection.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 22:53:52 2015 alexis mestag
// Last update Thu Jul  9 23:05:41 2015 alexis mestag
//

#ifndef		__UICONNECTION_HH__
# define	__UICONNECTION_HH__

# include	"Network/AbstractConnection.hh"

class	UIConnection : public AbstractConnection
{
public:
  explicit UIConnection(boost::asio::ip::tcp::socket socket,
			ConnectionManager &connectionManager);

public:
  virtual void	start() override;
};

#endif
