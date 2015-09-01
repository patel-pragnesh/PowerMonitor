//
// Reading.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Jun 20 22:23:27 2015 alexis mestag
// Last update Mon Aug 24 23:05:23 2015 alexis mestag
//

#ifndef			__READING_HH__
# define		__READING_HH__

# include	<memory>

# include	<odb/core.hxx>

# include	"Entities/Entity.hh"
# include	"Entities/Information.hh"
# include	"Entities/SlaveModule.hh"
# include	"Utils/Time.hh"

class	Reading : public Entity
{
  friend class	odb::access;

private:
  std::shared_ptr<SlaveModule const>	_module;
  Time::Point				_tp;
  Information				_info;

private:
  Reading() = default;

public:
  Reading(std::shared_ptr<SlaveModule const> module, Time::Point const &tp, Information const &i);

  Reading(Reading const &rhs) = delete;
  Reading	&operator=(Reading const &rhs) = delete;
  ~Reading() = default;

public:
  SlaveModule const	&getModule() const { return (*_module); }
  Time::Point const	&getTimePoint() const { return (_tp); }
  Information const	&getInformation() const { return (_info); }

  virtual void		serialize(Json::Value &json) const override;
};

# ifdef	ODB_COMPILER
#  pragma db object(Reading)
#  pragma db member(Reading::_module) not_null
#  pragma db member(Reading::_tp)
#  pragma db member(Reading::_info)
# endif

#endif
