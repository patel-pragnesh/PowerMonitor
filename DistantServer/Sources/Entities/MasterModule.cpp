//
// MasterModule.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat May 30 21:50:03 2015 alexis mestag
// Last update Fri Jun  5 07:18:57 2015 laurent ansel
//

#include	"Entities/MasterModule.hh"

MasterModule::MasterModule(std::string const &uuid, Connection *network) :
  Entity(),
  _uuid(uuid)
{
  setNetwork(network);
}

std::string const	&MasterModule::getUUID() const {
  return (_uuid);
}

void			MasterModule::setUUID(std::string const &uuid) {
  _uuid = uuid;
}
