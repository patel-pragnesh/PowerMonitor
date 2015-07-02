//
// TimeSlot.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  2 00:18:27 2014 alexis mestag
// Last update Wed May  6 19:50:07 2015 alexis mestag
//

#include		<utility>
#include		"Entities/TimeSlot.hh"

TimeSlot::TimeSlot(Week::Point &&beg, Week::Point &&end, std::shared_ptr<Profile const> const &profile) :
  Entity(),
  _beg(std::move(beg)), _end(std::move(end)), _profile(profile) {
}

bool			TimeSlot::operator==(TimeSlot const &rhs) const {
  return (this->getBeg() == rhs.getBeg() &&
	  this->getEnd() == rhs.getEnd());
}

bool			TimeSlot::operator!=(TimeSlot const &rhs) const {
  return !(*this == rhs);
}

Week::Point const	&TimeSlot::getBeg() const {
  return (_beg);
}

Week::Point const	&TimeSlot::getEnd() const {
  return (_end);
}

void			TimeSlot::setBeg(Week::Point const &beg) {
  _beg = beg;
}

void			TimeSlot::setEnd(Week::Point const &end) {
  _end = end;
}

void			TimeSlot::serialize(Json::Value &json) const {
  Entity::serialize(json);
  _beg.serialize(json["beg"]);
  _end.serialize(json["end"]);
}
