//
// Entity.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Nov 29 00:26:03 2014 alexis mestag
// Last update Fri Jun  5 07:21:58 2015 laurent ansel
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

Connection		&Entity::getNetwork() const {
  return (*_network);
}

void			Entity::setNetwork(Connection *network) {
  _network = network;
}

bool			Entity::isConnect() const
{
  if (_network)
    return (true);
  return (false);
}

void			Entity::serialize(Json::Value &json) const {
  json["id"] = static_cast<Json::UInt64>(_id);
}
