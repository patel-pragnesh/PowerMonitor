//
// TimeSlot.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  2 00:13:56 2014 alexis mestag
// Last update Mon Apr 13 21:44:12 2015 alexis mestag
//

#ifndef			__TIMESLOT_HH__
# define		__TIMESLOT_HH__

# include		<odb/core.hxx>

# include		"Entities/Entity.hh"
# include		"Entities/Profile.hh"
# include		"Entities/Week.hh"

class			TimeSlot : public Entity
{
  friend class		odb::access;

private:
  Week::Point				_beg;
  Week::Point				_end;
  std::shared_ptr<Profile const>	_profile;

private:
  TimeSlot() = default;

public:
  TimeSlot(Week::Point &&beg, Week::Point &&end, std::shared_ptr<Profile const> const &profile);
  TimeSlot(TimeSlot const &rhs) = default;

  TimeSlot		&operator=(TimeSlot const &rhs) = default;

  ~TimeSlot() = default;
  
public:
  bool			operator==(TimeSlot const &rhs) const;
  bool			operator!=(TimeSlot const &rhs) const;

  Week::Point const	&getBeg() const;
  void			setBeg(Week::Point const &beg);

  Week::Point const	&getEnd() const;
  void			setEnd(Week::Point const &end);

public:
  virtual void		serialize(Json::Value &json) const override;
};

# ifdef	ODB_COMPILER
#  pragma db object(TimeSlot)
#  pragma db member(TimeSlot::_beg)
#  pragma db member(TimeSlot::_end)
#  pragma db member(TimeSlot::_profile)
# endif

#endif
