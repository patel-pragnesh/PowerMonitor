//
// Time.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Dec 26 15:06:33 2014 alexis mestag
// Last update Sat Jun 20 23:49:20 2015 alexis mestag
//

#ifndef			__TIME_HH__
# define		__TIME_HH__

# include		<chrono>
# include		<odb/core.hxx>

# include		"Utils/ISerializable.hh"

namespace		Time {
  typedef std::chrono::system_clock	clock;
  typedef clock::time_point		time_point;
  typedef time_point::duration		duration;
  typedef time_point::rep		rep;
  
  class			Point : public ISerializable
  {
    friend class	odb::access;

  private:
    time_point		_point;

  public:
    Point() = default;
    Point(time_point const &time_point);
    Point(rep const &rep);
    Point(Point const &rhs) = default;

    Point		&operator=(Point const &rhs) = default;
    
    ~Point() = default;

  public:
    bool		operator<(Point const &rhs) const;
    bool		operator<=(Point const &rhs) const;
    bool		operator>=(Point const &rhs) const;
    bool		operator==(Point const &rhs) const;
    bool		operator!=(Point const &rhs) const;

    time_point const	&getTimePoint() const;
    void		setTimePoint(time_point const &time_point);

    rep			getTimeSinceEpoch() const;

  public:
    virtual void	serialize(Json::Value &json) const override;
    
  private:
    void		setFromTimeSinceEpoch(rep const time);
  };
}

# ifdef	ODB_COMPILER
#  pragma db value(Time::Point) transient
#  pragma db member(Time::Point::point) virtual(Time::rep) get(getTimeSinceEpoch()) set(setFromTimeSinceEpoch(?))
# endif

#endif
