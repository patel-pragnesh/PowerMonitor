//
// DefaultProfile.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Nov 29 02:01:33 2014 alexis mestag
// Last update Tue Feb 10 17:19:40 2015 alexis mestag
//

#ifndef			__DEFAULTPROFILE_HH__
# define		__DEFAULTPROFILE_HH__

# include		<list>
# include		<memory>
# include		"Entities/Profile.hh"

# include		<odb/core.hxx>

class			SlaveModule;

class			DefaultProfile : public Profile
{
  friend class		odb::access;

public:
  typedef std::list<std::weak_ptr<SlaveModule const>>	ModulesList;
  
private:
  std::string		_name;
  ModulesList		_modules;

private:
  DefaultProfile() = default;

public:
  DefaultProfile(DefaultProfile const &rhs) = delete;
  DefaultProfile(std::string const &name, int const polling);
  ~DefaultProfile() = default;

  DefaultProfile	&operator=(DefaultProfile const &rhs) = delete;

public:
  std::string const	&getName() const;
  void			setName(std::string const &name);

  ModulesList const	&getModules() const;

public:
  virtual void		serialize(Json::Value &json) const override;
};

# include		"Entities/SlaveModule.hh"

# ifdef	ODB_COMPILER
#  pragma db object(DefaultProfile)
#  pragma db member(DefaultProfile::_name)
#  pragma db member(DefaultProfile::_modules) inverse(_defaultProfile) value_not_null
# endif

#endif
