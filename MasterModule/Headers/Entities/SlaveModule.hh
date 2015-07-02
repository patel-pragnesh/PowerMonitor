//
// SlaveModule.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Nov 29 00:59:44 2014 alexis mestag
// Last update Sat Jun 20 22:11:03 2015 alexis mestag
//

#ifndef			__SLAVEMODULE_HH__
# define		__SLAVEMODULE_HH__

# include		<map>
# include		<memory>
# include		<string>
# include		"Entities/Entity.hh"
# include		"Entities/DefaultProfile.hh"
# include		"Entities/InternalProfile.hh"
# include		"Utils/Time.hh"

# include		<odb/core.hxx>

class			SlaveModule : public Entity
{
  friend class		odb::access;

public:
  typedef std::shared_ptr<DefaultProfile const>	DefaultProfilePointer;
  typedef std::shared_ptr<InternalProfile>	InternalProfilePointer;
  
private:
  std::string					_name;
  std::string					_serialNumber;
  bool						_status;
  DefaultProfilePointer                     	_defaultProfile;
  InternalProfilePointer			_internalProfile;
  // std::map<Time::Point, Information>		_informations;

private:
  SlaveModule() = default;

public:
  SlaveModule(SlaveModule const &rhs) = delete;
  SlaveModule(std::string const &name, std::string const &serialNumber);
  ~SlaveModule() = default;

  SlaveModule		&operator=(SlaveModule const &rhs) = delete;

public:
  std::string const	&getName() const;
  void			setName(std::string const &name);

  std::string const	&getSerialNumber() const;
  void			setSerialNumber(std::string const &serialNumber);

  bool			getStatus() const;
  void			setStatus(bool const status);

  DefaultProfilePointer	getDefaultProfile() const;
  void			setDefaultProfile(DefaultProfilePointer const &defaultProfile);

  InternalProfilePointer	getInternalProfile() const;

public:
  virtual void		serialize(Json::Value &json) const override;
};

# ifdef	ODB_COMPILER
#  pragma db object(SlaveModule)
#  pragma db member(SlaveModule::_name)
#  pragma db member(SlaveModule::_serialNumber)
#  pragma db member(SlaveModule::_defaultProfile)
#  pragma db member(SlaveModule::_internalProfile)
// #  pragma db member(SlaveModule::_informations)
# endif

#endif
