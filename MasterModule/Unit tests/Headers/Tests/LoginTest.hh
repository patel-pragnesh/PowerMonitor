//
// LoginTest.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule/Unit tests/c++
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Apr 15 17:08:26 2015 alexis mestag
// Last update Fri Apr 17 23:24:50 2015 alexis mestag
//

#ifndef			__LOGINTEST_HH__
# define		__LOGINTEST_HH__

# include		"UnitTest.hh"

class			LoginTest : public UnitTest
{
public:
  LoginTest(UnitTestsClient &client);
  ~LoginTest() = default;

public:
  virtual bool		operator()() override;

private:
  bool			badUser();
  bool			badPassword();
  bool			loginOk();
};

#endif
