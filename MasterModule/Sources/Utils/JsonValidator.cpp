//
// JsonValidator.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule/Tests
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Feb 22 18:48:17 2015 alexis mestag
// Last update Sun Mar 29 18:22:29 2015 alexis mestag
//

#include		<algorithm>
#include		<iostream>
#include		"Utils/JsonValidator.hh"

JsonValidator::JsonValidator(std::initializer_list<pair_type> const &il) :
  _predicate(std::mem_fn(&Json::Value::isObject)), _members(il) {
}

bool			JsonValidator::operator()(Json::Value const &json) const {
  bool			ret;

  if (_predicate) {
    ret = false;
    if (_predicate(json)) {
      ret = std::all_of(_members.begin(), _members.end(),
			[&](pair_type const &pair) {
			  return (pair.second(json[pair.first]));
			});
    }
  } else { // returns true is predicate is not callable (i.e JsonValidator default constructed)
    ret = true;
  }
  return (ret);
}

bool			JsonValidator::isNonEmptyString(Json::Value const &json) {
  return (json.isString() && !json.asString().empty());
}
