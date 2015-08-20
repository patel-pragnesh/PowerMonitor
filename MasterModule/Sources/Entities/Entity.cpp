//
// Entity.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Nov 29 00:26:03 2014 alexis mestag
// Last update Tue Feb 10 17:15:41 2015 alexis mestag
//

#include		"Entities/Entity.hh"

Entity::Entity(unsigned long id) :
  _id(id) {
}

void			Entity::setId(unsigned long const id) {
  _id = id;
}

unsigned long		Entity::getId() const {
  return (_id);
}

void			Entity::serialize(Json::Value &json) const {
  json["id"] = static_cast<Json::UInt64>(_id);
}
