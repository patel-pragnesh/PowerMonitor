//
// UIHandler.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Jul  6 18:18:26 2015 alexis mestag
// Last update Mon Jul  6 18:24:02 2015 alexis mestag
//

#ifndef		__UIHANDLER_HH__
# define	__UIHANDLER_HH__

# include	<string>
# include	<boost/asio.hpp>

using	boost::asio::ip::tcp;

class	UIHandler
{
private:
  boost::asio::io_service	&_ios;
  tcp::acceptor			_acceptor;
  tcp::socket			_socket;

public:
  UIHandler(boost::asio::io_service &ios,
	    std::string &&address,
	    std::string &&port);

  void	stop();

private:
  void	accept();
};

#endif
