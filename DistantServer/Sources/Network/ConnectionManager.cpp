//
// ConnectionManager.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 28 02:46:57 2015 alexis mestag
// Last update Sat May 30 19:06:18 2015 alexis mestag
//

#include		<algorithm>
#include		"Network/ConnectionManager.hh"

void			ConnectionManager::start(Connections::value_type c) {
  _connections.insert(c);
  c->start();
}

void			ConnectionManager::stop(Connections::value_type c) {
  _connections.erase(c);
  c->stop();
}

void			ConnectionManager::stop() {
  std::for_each(_connections.begin(), _connections.end(),
		[](Connections::value_type c) {
		  c->stop();
		});
  _connections.clear();
}
