//
// DefaultProfileRepository.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Apr  4 21:32:52 2015 alexis mestag
// Last update Sat Apr  4 21:36:04 2015 alexis mestag
//

#ifndef			__DEFAULTPROFILEREPOSITORY_HH__
# define		__DEFAULTPROFILEREPOSITORY_HH__

# include		"Database/Repository.hpp"
# include		"Entities/DefaultProfile-odb.hxx"

class			DefaultProfileRepository : public Repository<DefaultProfile>
{
public:
  DefaultProfileRepository() = delete;
  DefaultProfileRepository(DefaultProfileRepository const &rhs) = delete;
  DefaultProfileRepository	&operator=(DefaultProfileRepository const &rhs) = delete;

  DefaultProfileRepository(Database &database);
  ~DefaultProfileRepository() = default;

public:
  Repository<DefaultProfile>::pointer_type	getByName(std::string const &name);
};

#endif
