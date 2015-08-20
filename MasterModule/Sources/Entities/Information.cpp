//
// Information.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  2 01:32:16 2014 alexis mestag
// Last update Sat Jun 20 22:13:16 2015 alexis mestag
//

#include		"Entities/Information.hh"

Information::Information(std::shared_ptr<Unit const> unit, double const value) :
  _unit(std::move(unit)), _value(value) {
}

bool			Information::operator==(Information const &rhs) const {
  return (_value == rhs.getValue() && this->getUnit() == rhs.getUnit());
}

bool			Information::operator!=(Information const &rhs) const {
  return !(*this == rhs);
}

double			Information::getValue() const {
  return (_value);
}

void			Information::setValue(double const value) {
  _value = value;
}

Unit const		&Information::getUnit() const {
  return (*_unit);
}

void			Information::setUnit(std::shared_ptr<Unit const> unit) {
  _unit = std::move(unit);
}

void			Information::serialize(Json::Value &json) const {
  json["value"] = _value;
  json["unitId"] = static_cast<Json::UInt64>(_unit->getId());
}
