//
// UserRepository.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Feb 21 23:34:57 2015 alexis mestag
// Last update Mon Feb 23 01:29:11 2015 alexis mestag
//

#include			"Database/UserRepository.hh"

UserRepository::UserRepository(Database &database) :
  Repository<User>(database) {

}

Repository<User>::pointer_type	UserRepository::getByEmail(std::string const &email) {
  Repository<User>::pointer_type	ret = nullptr;
  Repository<User>::query_type		query(Repository<User>::query_type::email == email);
  Repository<User>::result_type		result(_database.query(query));

  if (result.size()) {
    ret = result.begin().load();
  }
  return (ret);
}
