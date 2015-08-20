//
// UnitTestsClient.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule/Unit tests
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Apr 14 17:49:33 2015 alexis mestag
// Last update Sat Apr 18 19:26:27 2015 alexis mestag
//

#ifndef		__UNITTESTSCLIENT_HH__
# define	__UNITTESTSCLIENT_HH__

# include	<string>

# include	<boost/asio.hpp>
# include	<json/value.h>

# include	"Logger.hh"

using		boost::asio::ip::tcp;

class		UnitTestsClient
{
private:
  boost::asio::io_service	_ios;
  tcp::socket			_socket;
  Logger			_logger;
  Json::Value			_session;

public:
  UnitTestsClient() = delete;
  UnitTestsClient(UnitTestsClient const &rhs) = delete;
  UnitTestsClient	&operator=(UnitTestsClient const &rhs) = delete;

  UnitTestsClient(std::string const &address, std::string const &port);
  ~UnitTestsClient() = default;

public:
  void		run();

  void		send(Json::Value const &request);
  void		recv(Json::Value &response);

  Logger	&log();
};

#endif
