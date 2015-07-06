//
// ConnectionManager.hpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Jul  6 19:19:13 2015 alexis mestag
// Last update Mon Jul  6 21:17:20 2015 alexis mestag
//

#ifndef		__CONNECTIONMANAGER_HPP__
# define	__CONNECTIONMANAGER_HPP__

# include	<algorithm>
# include	<memory>
# include	<set>
# include	<utility>

template<typename C>
class		ConnectionManager
{
public:
  using ConnectionType		= C;
  using ConnectionPtr		= std::shared_ptr<ConnectionType>;
  using ConnectionsContainer	= std::set<ConnectionPtr>;

private:
  ConnectionsContainer	_connections;

public:
  ConnectionManager(ConnectionManager const &rhs) = delete;
  ConnectionManager	&operator=(ConnectionManager const &rhs) = delete;

  ConnectionManager() = default;
  ~ConnectionManager() = default;

public:
  void		start(typename ConnectionsContainer::value_type &&c) {
    std::pair<typename ConnectionsContainer::iterator,
	      bool> in = _connections.insert(std::forward<typename ConnectionsContainer::value_type>(c));
    if (in.second) {
      (*in.first)->start();
    }
  }
  void		stop(typename ConnectionsContainer::value_type c) {
    _connections.erase(c);
    c->stop();
  }
  void		stop() {
    std::for_each(_connections.begin(), _connections.end(),
		  [](typename ConnectionsContainer::value_type c) {
		    c->stop();
		  });
  }
};

#endif
