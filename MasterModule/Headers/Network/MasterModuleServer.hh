//
// MasterModuleServer.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Jan 24 18:45:59 2015 alexis mestag
// Last update Mon Feb 23 00:52:33 2015 alexis mestag
//

#ifndef			__MASTERMODULESERVER_HH__
# define		__MASTERMODULESERVER_HH__

# include		<string>
# include		<boost/asio.hpp>
# include		"Database/Database.hh"
# include		"Network/ConnectionManager.hh"
# include		"Network/RequestHandler.hh"

using			boost::asio::ip::tcp;

class			MasterModuleServer
{
private:
  boost::asio::io_service	_ios;
  boost::asio::signal_set	_signals;
  tcp::acceptor			_acceptor;
  tcp::socket			_socket;
  Database			_database;
  ConnectionManager		_connectionManager;

public:
  MasterModuleServer() = delete;
  MasterModuleServer(MasterModuleServer const &rhs) = delete;

  MasterModuleServer	&operator=(MasterModuleServer const &rhs) = delete;

  MasterModuleServer(std::string const &address, std::string const &port);
  ~MasterModuleServer() = default;

  void			run();

private:
  void			handleSignals();
  void			handleAccept();
};

#endif
