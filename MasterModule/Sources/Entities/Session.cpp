//
// Session.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/ODB
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon May  4 03:21:50 2015 alexis mestag
// Last update Sat Jun 20 21:34:23 2015 alexis mestag
//

#include	<algorithm>
#include	<functional>
#include	<limits>
#include	<random>

#include	"Entities/Session.hh"
#include	"Utils/Bytes.hpp"

Session::Session(std::shared_ptr<User> const &user) :
  Entity(),
  _user(user) {
  this->generateToken();
}

Session::Session(std::shared_ptr<User> &&user) :
  Entity(),
  _user(std::move(user)) {
  this->generateToken();
}

void				Session::generateToken() {
  std::random_device					gen;
  std::uniform_int_distribution<token_type::value_type>	dist(std::numeric_limits<token_type::value_type>::min(),
							     std::numeric_limits<token_type::value_type>::max());

  std::generate(_token.begin(), _token.end(), std::bind(dist, std::ref(gen)));
}

std::shared_ptr<User>		Session::getUser() {
  return (_user);
}

Session::token_type const	&Session::getToken() const {
  return (_token);
}

void				Session::serialize(Json::Value &json) const {
  json["userId"] = static_cast<Json::UInt64>(_user->getId());
  json["token"] = Bytes::hexEncode(_token);
}
