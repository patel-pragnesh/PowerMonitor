//
// ConnectionManager.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 28 00:01:43 2015 alexis mestag
// Last update Sat May 30 18:58:00 2015 alexis mestag
//

#ifndef			__CONNECTIONMANAGER_HH__
# define		__CONNECTIONMANAGER_HH__

# include		<set>
# include		"Network/Connection.hh"

class			ConnectionManager
{
private:
  typedef std::set<std::shared_ptr<Connection>>	Connections;

private:
  Connections		_connections;

public:
  ConnectionManager(ConnectionManager const &rhs) = delete;
  ConnectionManager	&operator=(ConnectionManager const &rhs) = delete;

  ConnectionManager() = default;
  ~ConnectionManager() = default;

public:
  void			start(Connections::value_type c);
  void			stop(Connections::value_type c);
  void			stop();
};

#endif
