//
// ModuleTest.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Jul  7 22:11:06 2015 alexis mestag
// Last update Tue Jul  7 22:12:50 2015 alexis mestag
//

#ifndef		__MODULETEST_HH__
# define	__MODULETEST_HH__

# include	"UnitTest.hh"

class		ModuleTest : public UnitTest
{
public:
  ModuleTest(UnitTestsClient &client);
  ~ModuleTest() = default;

public:
  virtual bool	operator()() override;

private:
  bool		getModuleConso();
};

#endif
