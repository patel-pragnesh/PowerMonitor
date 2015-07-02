//
// Unit.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  2 00:57:39 2014 alexis mestag
// Last update Tue Feb 10 20:54:03 2015 alexis mestag
//

#include		"Entities/Unit.hh"

Unit::Unit(std::string const &name, std::string const &symbol) :
  Entity(),
  _name(name), _symbol(symbol) {
}

bool			Unit::operator==(Unit const &rhs) const {
  return (_name == rhs.getName() && _symbol == rhs.getSymbol());
}

bool			Unit::operator!=(Unit const &rhs) const {
  return !(*this == rhs);
}

std::string const	&Unit::getName() const {
  return (_name);
}

void			Unit::setName(std::string const &name) {
  _name = name;
}

std::string const	&Unit::getSymbol() const {
  return (_symbol);
}

void			Unit::setSymbol(std::string const &symbol) {
  _symbol = symbol;
}

void			Unit::serialize(Json::Value &json) const {
  Entity::serialize(json);
  json["name"] = _name;
  json["symbol"] = _symbol;
}
