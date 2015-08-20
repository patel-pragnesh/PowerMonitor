//
// UIHandler.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue May 26 22:19:42 2015 alexis mestag
// Last update Wed May 27 02:50:16 2015 alexis mestag
//

#ifndef		__UIHANDLER_HH__
# define	__UIHANDLER_HH__

# include	<string>
# include	<boost/asio.hpp>

# include	"Database/Database.hh"
# include	"Network/ConnectionManager.hh"

using	boost::asio::ip::tcp;

class	UIHandler
{
private:
  tcp::acceptor		_acceptor;
  tcp::socket		_socket;
  Database		_database;
  ConnectionManager	_connectionManager;

public:
  UIHandler(boost::asio::io_service &ios,
	    std::string const &address,
	    std::string const &port);

  void	stop();

private:
  void	accept();
};

#endif
