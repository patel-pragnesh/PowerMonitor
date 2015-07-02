//
// WeekPoint.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Apr  4 23:17:37 2015 alexis mestag
// Last update Sat Apr 11 21:41:05 2015 alexis mestag
//

#ifndef			__WEEK_HH__
# define		__WEEK_HH__

# include		<odb/core.hxx>

# include		"Utils/ISerializable.hh"

namespace		Week {
  enum			Day {
    Monday = 0,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
  };

  Day			toWeekDay(unsigned int const i);
  
  class			Point : public ISerializable
  {
    friend class	odb::access;

  private:
    Day			_day;
    unsigned int	_minute;

  public:
    Point() = default;
    Point(Day const &day, unsigned int const minute);
    Point(Point const &rhs) = default;
    Point		&operator=(Point const &rhs) = default;
    ~Point() = default;

  public:
    bool		operator==(Point const &rhs) const;
    bool		operator!=(Point const &rhs) const;
    
  public:
    Day const		&getDay() const;
    void		setDay(Day const &day);

    unsigned int	getMinute() const;
    void		setMinute(unsigned int const minute);

    virtual void	serialize(Json::Value &json) const override;
  };
}

# ifdef	ODB_COMPILER
#  pragma db value(Week::Point)
#  pragma db member(Week::Point::_day)
#  pragma db member(Week::Point::_minute)
# endif

#endif
