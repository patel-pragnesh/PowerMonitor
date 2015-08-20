//
// User.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/ODB
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun May  3 23:25:55 2015 alexis mestag
// Last update Sat Jun 20 21:40:32 2015 alexis mestag
//

#include		<utility>

#include		<cryptopp/sha.h>

#include		"Entities/User.hh"

User::User(std::string const &name,
	   std::string const &surname,
	   std::string const &email) :
  Entity(),
  _name(name), _surname(surname), _email(email) {
}

User::User(std::string &&name,
	   std::string &&surname,
	   std::string &&email) :
  Entity(),
  _name(std::move(name)), _surname(std::move(surname)), _email(std::move(email)) {
}

std::string const	&User::getName() const {
  return (_name);
}

void			User::setName(std::string const &name) {
  _name = name;
}

void			User::setName(std::string &&name) {
  _name = std::move(name);
}

std::string const	&User::getSurname() const {
  return (_surname);
}

void			User::setSurname(std::string const &surname) {
  _surname = surname;
}

void			User::setSurname(std::string &&surname) {
  _surname = std::move(surname);
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

User::hash_type const	&User::getHash() const {
  return (_hash);
}

User::salt_type const	&User::getSalt() const {
  return (_salt);
}

void			User::setPassword(std::string const &password) {
  CryptoPP::SHA256	sha;

  sha.Update((byte const *)password.data(), password.size());
  sha.Update((byte const *)_salt.data(), _salt.size());
  sha.Final(_hash.data());
}

void			User::serialize(Json::Value &json) const {
  Entity::serialize(json);
  json["name"] = _name;
  json["surname"] = _surname;
  json["email"] = _email;
}
