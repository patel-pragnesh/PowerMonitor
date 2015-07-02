//
// InternProfile.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Nov 29 02:22:57 2014 alexis mestag
// Last update Wed Apr  8 17:46:25 2015 alexis mestag
//

#ifndef			__INTERNALPROFILE_HH__
# define		__INTERNALPROFILE_HH__

# include		<memory>
# include		"Entities/Profile.hh"

# include		<odb/core.hxx>

class			SlaveModule;

class			InternalProfile : public Profile
{
  friend class		odb::access;

public:
  typedef std::weak_ptr<SlaveModule const>	SlaveModulePointer;
  
private:
  SlaveModulePointer	_module;

private:
  InternalProfile() = default;

public:
  InternalProfile(int const polling);
  InternalProfile(InternalProfile const &rhs) = delete;
  ~InternalProfile() = default;

  InternalProfile		&operator=(InternalProfile const &rhs) = delete;

public:
  SlaveModulePointer const	&getModule() const;

public:
  virtual void			serialize(Json::Value &json) const override;
};

# include		"Entities/SlaveModule.hh"

# ifdef	ODB_COMPILER
#  pragma db object(InternalProfile)
#  pragma db member(InternalProfile::_module) inverse(_internalProfile)
# endif

#endif
