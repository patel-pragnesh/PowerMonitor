//
// ConnectionManager.hpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Jul  6 19:19:13 2015 alexis mestag
// Last update Thu Jul  9 22:49:18 2015 alexis mestag
//

#ifndef		__CONNECTIONMANAGER_HH__
# define	__CONNECTIONMANAGER_HH__

# include	<memory>
# include	<set>

class		AbstractConnection;

class		ConnectionManager
{
  using ConnectionPtr		= std::shared_ptr<AbstractConnection>;
  using ConnectionsContainer	= std::set<ConnectionPtr>;

private:
  ConnectionsContainer	_connections;

public:
  ConnectionManager(ConnectionManager const &rhs) = delete;
  ConnectionManager	&operator=(ConnectionManager const &rhs) = delete;

  ConnectionManager() = default;
  ~ConnectionManager() = default;

public:
  void		start(typename ConnectionsContainer::value_type &&c);
  void		stop(typename ConnectionsContainer::value_type c);
  void		stop();
};

# include	"Network/AbstractConnection.hh"

#endif
