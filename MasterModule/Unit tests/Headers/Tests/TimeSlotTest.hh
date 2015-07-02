//
// TimeSlotTest.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule/Unit tests
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Apr 29 22:03:50 2015 alexis mestag
// Last update Wed Apr 29 22:08:37 2015 alexis mestag
//

#ifndef			__TIMESLOTTEST_HH__
# define		__TIMESLOTTEST_HH__

# include		"UnitTest.hh"

class			TimeSlotTest : public UnitTest
{
private:
  Json::Value		_profiles;
  Json::Value		_profile;
  Json::Value		_timeSlots;
  Json::Value		_addedTimeSlotId;

public:
  TimeSlotTest(UnitTestsClient &client);
  ~TimeSlotTest() = default;

public:
  virtual bool		operator()() override;

private:
  bool			getProfiles();

  bool			addTimeSlot();
  bool			regettingTimeSlots();
  bool			addTimeSlotProfileNotFound();

  bool			updateTimeSlot();
  bool			updateTimeSlotNotFound();

  bool			deleteTimeSlot();
  bool			checkIfTimeSlotDeleted();
  bool			deleteTimeSlotNotFound();
};

#endif
