//
// Profile.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Nov 29 01:11:10 2014 alexis mestag
// Last update Sun Apr  5 19:47:48 2015 alexis mestag
//

#ifndef			__PROFILE_HH__
# define		__PROFILE_HH__

# include		<list>
# include		<memory>
# include		<string>
# include		<odb/core.hxx>

# include		"Entities/Entity.hh"

class			Alert;
class			TimeSlot;

class			Profile : public Entity
{
  friend class		odb::access;

public:
  typedef std::list<std::weak_ptr<Alert>>	Alerts;
  typedef std::list<std::weak_ptr<TimeSlot>>	TimeSlots;

private:
  int			_polling;
  Alerts		_alerts;
  TimeSlots		_timeSlots;

protected:
  Profile() = default;
  Profile(Profile const &rhs) = default;

  Profile		&operator=(Profile const &rhs) = default;

  Profile(int const polling);

public:
  virtual ~Profile() = default;

public:
  int			getPolling() const;
  void			setPolling(int const polling);

  Alerts const		&getAlerts() const;
  void			setAlerts(Alerts const &alerts);
  void			addAlert(Alerts::value_type const &alert);
  void			removeAlert(Alerts::value_type const &alert);

  TimeSlots const	&getTimeSlots() const;
  void			setTimeSlots(TimeSlots const &timeSlots);
  void			addTimeSlot(TimeSlots::value_type const &timeSlot);
  void			removeTimeSlot(TimeSlots::value_type const &timeSlot);

public:
  virtual void		serialize(Json::Value &json) const override;
};

# include		"Entities/Alert.hh"
# include		"Entities/TimeSlot.hh"

# ifdef	ODB_COMPILER
#  pragma db object(Profile) polymorphic
#  pragma db member(Profile::_polling)
#  pragma db member(Profile::_alerts) inverse(_profile) value_not_null
#  pragma db member(Profile::_timeSlots) inverse(_profile) value_not_null
# endif

#endif
