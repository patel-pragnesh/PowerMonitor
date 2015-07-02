//
// Alert.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  2 00:37:50 2014 alexis mestag
// Last update Sun Apr 12 23:05:09 2015 alexis mestag
//

#include		<utility>
#include		"Entities/Alert.hh"

Alert::Alert(Information &&information, std::shared_ptr<Profile> const &profile) :
  Entity(),
  _information(std::move(information)), _profile(profile) {
}

bool			Alert::operator==(Alert const &rhs) const {
  return (_information == rhs.getInformation());
}

bool			Alert::operator!=(Alert const &rhs) const {
  return !(*this == rhs);
}

Information const	&Alert::getInformation() const {
  return (_information);
}

void			Alert::setInformation(Information const &information) {
  _information = information;
}

void			Alert::setUnit(std::shared_ptr<Unit const> const &unit) {
  _information.setUnit(unit);
}

void			Alert::setValue(double const value) {
  _information.setValue(value);
}

Alert::Users const	&Alert::getUsers() const {
  return (_users);
}

void			Alert::setUsers(Users const &users) {
  _users = users;
}

void			Alert::addUser(Users::value_type const &user) {
  _users.insert(user);
}

void			Alert::removeUser(Users::value_type const &user) {
  _users.erase(user);
}

void			Alert::serialize(Json::Value &json) const {
  Entity::serialize(json);
  _information.serialize(json);
}
