//
// MasterModuleRepository.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat May 30 22:16:37 2015 alexis mestag
// Last update Sat May 30 22:20:47 2015 alexis mestag
//

#ifndef		__MASTERMODULEREPOSITORY_HH__
# define	__MASTERMODULEREPOSITORY_HH__

# include	"Entities/MasterModule-odb.hxx"
# include	"Database/Repository.hpp"

class		MasterModuleRepository : public Repository<MasterModule>
{
public:
  MasterModuleRepository(Database &database);

public:
  Repository<MasterModule>::pointer_type	getByUUID(std::string const &uuid);
};

#endif
