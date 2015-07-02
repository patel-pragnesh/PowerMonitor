//
// DefaultProfileRepository.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Apr  4 21:36:41 2015 alexis mestag
// Last update Sat Apr  4 21:39:02 2015 alexis mestag
//

#include			"Database/DefaultProfileRepository.hh"

DefaultProfileRepository::DefaultProfileRepository(Database &database) :
  Repository<DefaultProfile>(database) {
}

Repository<DefaultProfile>::pointer_type	DefaultProfileRepository::getByName(std::string const &name) {
  Repository<DefaultProfile>::pointer_type	ret = nullptr;
  Repository<DefaultProfile>::query_type	query(Repository<DefaultProfile>::query_type::name == name);
  Repository<DefaultProfile>::result_type	result(_database.query(query));

  if (result.size()) {
    ret = result.begin().load();
  }
  return (ret);
}
