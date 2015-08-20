//
// SlaveModuleCount.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Apr 23 00:32:08 2015 alexis mestag
// Last update Thu Apr 23 00:37:26 2015 alexis mestag
//

#ifndef			__SLAVEMODULECOUNT_HH__
# define		__SLAVEMODULECOUNT_HH__

# include		"Entities/SlaveModule.hh"

struct			SlaveModuleCount
{
  std::size_t		count;
};

# ifdef	ODB_COMPILER
#  pragma db view(SlaveModuleCount) object(SlaveModule)
#  pragma db member(SlaveModuleCount::count) column("COUNT(" + SlaveModule::_id + ")")
# endif

#endif
