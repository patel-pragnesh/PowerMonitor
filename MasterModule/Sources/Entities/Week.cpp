//
// Week.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Apr  4 23:34:09 2015 alexis mestag
// Last update Sat Apr 11 21:48:48 2015 alexis mestag
//

#include		<map>
#include		<vector>
#include		"Entities/Week.hh"

namespace		Week {

  Day			toWeekDay(unsigned int const i) {
    static std::vector<Day> const	&days = {
      Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
    };

    return (days[i % days.size()]);
  }
  
  Point::Point(Day const &day, unsigned int const minute) :
    _day(day), _minute(minute) {
  }

  bool			Point::operator==(Point const &rhs) const {
    return (_day == rhs._day && _minute == rhs._minute);
  }
  bool			Point::operator!=(Point const &rhs) const {
    return (!(*this == rhs));
  }
  
  Day const		&Point::getDay() const {
    return (_day);
  }
  void			Point::setDay(Day const &day) {
    _day = day;
  }

  unsigned int		Point::getMinute() const {
    return (_minute);
  }
  void			Point::setMinute(unsigned int const minute) {
    _minute = minute;
  }

  void			Point::serialize(Json::Value &json) const {
    json["day"] = _day;
    json["minute"] = _minute;
  }
}
