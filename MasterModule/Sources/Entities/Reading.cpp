//
// Reading.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Jun 20 22:36:27 2015 alexis mestag
// Last update Sun Jun 21 00:21:37 2015 alexis mestag
//

#include	"Entities/Reading.hh"

Reading::Reading(std::shared_ptr<SlaveModule const> module, Time::Point const &tp, Information const &i) :
  Entity(),
  _module(std::move(module)), _tp(tp), _info(i) {
}

void		Reading::serialize(Json::Value &json) const {
  json["moduleId"] = static_cast<Json::UInt64>(_module->getId());
  json["time"] = static_cast<Json::UInt64>(_tp.getTimeSinceEpoch());
  _info.serialize(json);
}
