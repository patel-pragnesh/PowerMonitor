//
// AbstractConnection.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 17:16:33 2015 alexis mestag
// Last update Thu Jul  9 22:49:26 2015 alexis mestag
//

#ifndef		__ABSTRACTCONNECTION_HH__
# define	__ABSTRACTCONNECTION_HH__

# include	<memory>
# include	<boost/asio.hpp>

# include	"Network/ConnectionManager.hh"

using	boost::asio::ip::tcp;

class		AbstractConnection : public std::enable_shared_from_this<AbstractConnection>
{
private:
  tcp::socket		_socket;
  ConnectionManager	&_connectionManager;

protected:
  AbstractConnection() = delete;
  AbstractConnection(AbstractConnection const &rhs) = delete;
  AbstractConnection	&operator=(AbstractConnection const &rhs) = delete;

  AbstractConnection(boost::asio::ip::tcp::socket socket,
		     ConnectionManager &connectionManager);
  virtual ~AbstractConnection() = default;

protected:
  tcp::socket	&socket() { return (_socket); }

public:
  virtual void	start() = 0;
  void		stop();
};

#endif
