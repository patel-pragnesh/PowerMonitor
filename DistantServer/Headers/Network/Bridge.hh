//
// Bridge.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Aug 25 23:51:43 2015 alexis mestag
// Last update Wed Aug 26 03:28:09 2015 alexis mestag
//

#ifndef		__BRIDGE_HH__
# define	__BRIDGE_HH__

# include	<array>
# include	<list>
# include	<boost/asio.hpp>

class	MasterModuleConnection;
class	UIConnection;

class	Bridge
{
public:
  using	token = std::array<unsigned char, 32>;

private:
//   boost::asio::io_service	&_ios;
  std::list<std::shared_ptr<MasterModuleConnection>>	_modules;
  std::map<token, std::shared_ptr<UIConnection>>	_tokenToUI;

public:
  // Bridge(boost::asio::io_service &ios);

  /*
  ** Read a request from UI
  ** Add dSession token to request
  ** Associate dSession with UIConnection
  ** Forward request to master module
  **   Find it & forward
  ** Read again
  */
  void		run(std::shared_ptr<UIConnection> c);

  /*
  ** Read response from master module
  ** Read dSession token
  ** Find UIConnection associated with dSession token
  ** Forward response to UI
  ** Read again
  */
  void		run(std::shared_ptr<MasterModuleConnection> c);
  void		registerModule(std::shared_ptr<MasterModuleConnection> c);

private:
  token		generateToken();
};

#endif
