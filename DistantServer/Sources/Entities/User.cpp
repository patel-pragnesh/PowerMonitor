//
// User.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/ODB
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun May  3 23:25:55 2015 alexis mestag
// Last update Thu Jul  9 22:43:35 2015 alexis mestag
//

#include		<utility>
#include		"Entities/User.hh"

User::User(std::string const &email) :
  Entity(),
  _email(email) {
}

User::User(std::string &&email) :
  Entity(),
  _email(std::move(email)) {
}

std::string const	&User::getEmail() const {
  return (_email);
}

void			User::setEmail(std::string const &email) {
  _email = email;
}

void			User::setEmail(std::string &&email) {
  _email = std::move(email);
}

std::shared_ptr<MasterModule const>	User::getModule() const {
  return (_module);
}

void					User::setModule(std::shared_ptr<MasterModule> module) {
  _module = std::move(module);
}

void			User::serialize(Json::Value &json) const {
  Entity::serialize(json);
  json["email"] = _email;
}
