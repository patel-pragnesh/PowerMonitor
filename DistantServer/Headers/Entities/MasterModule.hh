//
// MasterModule.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat May 30 21:38:59 2015 alexis mestag
// Last update Fri Jun  5 07:20:03 2015 laurent ansel
//

#ifndef		__MASTERMODULE_HH__
# define	__MASTERMODULE_HH__

# include	<string>

# include	<odb/core.hxx>

# include	"Entities/Entity.hh"

class		MasterModule : public Entity
{
  friend class	odb::access;

private:
  std::string	_uuid;

private:
  MasterModule() = default;

public:
  MasterModule(std::string const &uuid, Connection *network = NULL);
  ~MasterModule() = default;

public:
  std::string const	&getUUID() const;
  void			setUUID(std::string const &uuid);
};

# ifdef	ODB_COMPILER
#  pragma db object(MasterModule)
#  pragma db member(MasterModule::_uuid)
#  pragma db member(MasterModule::_network) transient
# endif

#endif
