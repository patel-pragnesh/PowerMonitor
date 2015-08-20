//
// InternProfile.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Nov 29 02:45:31 2014 alexis mestag
// Last update Wed Apr  8 17:48:35 2015 alexis mestag
//

#include		"Entities/InternalProfile.hh"

InternalProfile::InternalProfile(int const polling) :
  Profile(polling) {
}

InternalProfile::SlaveModulePointer const	&InternalProfile::getModule() const {
  return (_module);
}

void			InternalProfile::serialize(Json::Value &json) const {
  Profile::serialize(json);
}
