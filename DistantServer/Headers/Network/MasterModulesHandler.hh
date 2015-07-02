//
// MasterModulesHandler.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat May 30 18:39:03 2015 alexis mestag
// Last update Sun May 31 00:05:25 2015 alexis mestag
//

#ifndef		__MASTERMODULESHANDLER_HH__
# define	__MASTERMODULESHANDLER_HH__

# include	<string>
# include	<boost/asio.hpp>

# include	"Database/Database.hh"
# include	"Network/ConnectionManager.hh"

using	boost::asio::ip::tcp;

class		MasterModulesHandler
{
private:
  boost::asio::io_service	&_ios;
  tcp::acceptor			_acceptor;
  tcp::socket			_socket;
  ConnectionManager		_connectionManager;
  Database			_database;

public:
  MasterModulesHandler(boost::asio::io_service &ios,
		       std::string const &address,
		       std::string const &port);

  void		stop();

private:
  void		accept();
};

#endif
