//
// DefaultProfile.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Nov 29 02:40:18 2014 alexis mestag
// Last update Tue Feb 10 17:22:48 2015 alexis mestag
//

#include		"Entities/DefaultProfile.hh"

DefaultProfile::DefaultProfile(std::string const &name, int const polling) :
  Profile(polling), _name(name) {
}

std::string const			&DefaultProfile::getName() const {
  return (_name);
}

void					DefaultProfile::setName(std::string const &name) {
  _name = name;
}

DefaultProfile::ModulesList const	&DefaultProfile::getModules() const {
  return (_modules);
}

void					DefaultProfile::serialize(Json::Value &json) const {
  Profile::serialize(json);
  json["name"] = _name;
}

