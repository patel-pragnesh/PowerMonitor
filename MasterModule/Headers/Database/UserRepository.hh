//
// UserRepository.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Feb 21 23:25:29 2015 alexis mestag
// Last update Sat Feb 21 23:56:23 2015 alexis mestag
//

#ifndef			__USERREPOSITORY_HH__
# define		__USERREPOSITORY_HH__

# include		"Database/Repository.hpp"
# include		"Entities/User-odb.hxx"

class			UserRepository : public Repository<User>
{
public:
  UserRepository() = delete;
  UserRepository(UserRepository const &rhs) = delete;
  UserRepository	&operator=(UserRepository const &rhs) = delete;

  UserRepository(Database &database);
  ~UserRepository() = default;

public:
  Repository<User>::pointer_type	getByEmail(std::string const &email);
};

#endif
