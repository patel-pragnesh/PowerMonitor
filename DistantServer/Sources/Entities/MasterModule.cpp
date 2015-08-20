//
// MasterModule.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat May 30 21:50:03 2015 alexis mestag
// Last update Thu Jul  9 22:31:49 2015 alexis mestag
//

#include	"Entities/MasterModule.hh"

MasterModule::MasterModule(std::string const &uuid) :
  Entity(),
  _uuid(uuid) {
}

std::string const	&MasterModule::getUUID() const {
  return (_uuid);
}

void			MasterModule::setUUID(std::string const &uuid) {
  _uuid = uuid;
}
