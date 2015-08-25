//
// ConnectionManager.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 22:16:08 2015 alexis mestag
// Last update Thu Jul  9 22:50:15 2015 alexis mestag
//

#include	<algorithm>
#include	<utility>
#include	"Network/ConnectionManager.hh"

void	ConnectionManager::start(typename ConnectionsContainer::value_type &&c) {
  std::pair<typename ConnectionsContainer::iterator,
	    bool> in = _connections.insert(std::forward<typename ConnectionsContainer::value_type>(c));
  if (in.second) {
    (*in.first)->start();
  }
}

void	ConnectionManager::stop(typename ConnectionsContainer::value_type c) {
  _connections.erase(c);
  c->stop();
}
void	ConnectionManager::stop() {
  std::for_each(_connections.begin(), _connections.end(),
		[](typename ConnectionsContainer::value_type c) {
		  c->stop();
		});
}
