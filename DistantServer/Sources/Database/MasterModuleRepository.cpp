//
// MasterModuleRepository.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat May 30 22:21:00 2015 alexis mestag
// Last update Sat May 30 22:23:18 2015 alexis mestag
//

#include	"Database/MasterModuleRepository.hh"

MasterModuleRepository::MasterModuleRepository(Database &database) :
  Repository(database) {
}

Repository<MasterModule>::pointer_type	MasterModuleRepository::getByUUID(std::string const &uuid) {
  Repository<MasterModule>::pointer_type	ret = nullptr;
  Repository<MasterModule>::query_type		query(Repository<MasterModule>::query_type::uuid == uuid);
  Repository<MasterModule>::result_type		result(_database.query(query));

  if (result.size()) {
    ret = result.begin().load();
  }
  return (ret);
}
