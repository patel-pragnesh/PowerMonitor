//
// UnitTest.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule/Unit tests/c++
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Apr 14 18:53:28 2015 alexis mestag
// Last update Sat Apr 18 19:49:10 2015 alexis mestag
//

#ifndef			__UNITTEST_HH__
# define		__UNITTEST_HH__

# include		<string>

# include		<json/value.h>

# include		"Network/RequestHandler.hh"

class			UnitTestsClient;

class			UnitTest
{
private:
  std::string		_desc;
  UnitTestsClient	&_client;
  bool			_manageSession;
  Json::Value		_session;

protected:
  UnitTest(std::string &&desc, UnitTestsClient &client, bool manageSession = true);

public:
  virtual ~UnitTest() = default;

protected:
  bool			login();

  void			send(Json::Value &request);
  void			recv(Json::Value &response);

  bool			checkReturnCode(Json::Value const &response, RequestHandler::eReturnCode const &retCode);

  Logger		&log();
  
public:
  virtual bool		operator()() = 0;

  std::string const	&getDescription() const;
};

# include		"UnitTestsClient.hh"

#endif
