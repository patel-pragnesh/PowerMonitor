//
// AlertTest.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Apr 18 19:05:15 2015 alexis mestag
// Last update Sat Apr 18 22:41:00 2015 alexis mestag
//

#ifndef			__ALERTTEST_HH__
# define		__ALERTTEST_HH__

# include		"UnitTest.hh"

class			AlertTest : public UnitTest
{
private:
  Json::Value		_profiles;
  Json::Value		_profile;
  Json::Value		_alerts;
  Json::Value		_addedAlertId;

public:
  AlertTest(UnitTestsClient &client);
  ~AlertTest() = default;

public:
  virtual bool		operator()() override;

private:
  bool			getProfiles();

  bool			addAlert();
  bool			regettingAlerts();
  bool			addAlertNoSuchProfile();
  bool			addAlertNoSuchUnit();

  bool			updateAlert();
  bool			updateAlertNotFound();
  bool			updateAlertUnitNotFound();

  bool			deleteAlert();
  bool			checkIfAlertDeleted();
  bool			deleteAlertNotFound();
};

#endif
