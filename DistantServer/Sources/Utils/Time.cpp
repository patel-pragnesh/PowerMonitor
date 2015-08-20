//
// Time.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Dec 26 15:35:03 2014 alexis mestag
// Last update Tue Feb 10 20:24:34 2015 alexis mestag
//

#include		"Utils/Time.hh"

namespace		Time {
  Point::Point(time_point const &time_point) :
    _point(time_point) {
  }

  bool			Point::operator<(Point const &rhs) const {
    return (this->getTimePoint() < rhs.getTimePoint());
  }
  
  bool			Point::operator==(Point const &rhs) const {
    return (this->getTimePoint() == rhs.getTimePoint());
  }

  bool			Point::operator!=(Point const &rhs) const {
    return (!(*this != rhs));
  }
  
  time_point const	&Point::getTimePoint() const {
    return (_point);
  }

  void			Point::setTimePoint(time_point const &time_point) {
    _point = time_point;
  }

  void			Point::serialize(Json::Value &json) const {
    json["timestamp"] = static_cast<Json::Int64>(this->getTimeSinceEpoch());
  }
  
  rep			Point::getTimeSinceEpoch() const {
    return (_point.time_since_epoch().count());
  }

  void			Point::setFromTimeSinceEpoch(rep const time) {
    _point = time_point(duration(time));
  }
}
