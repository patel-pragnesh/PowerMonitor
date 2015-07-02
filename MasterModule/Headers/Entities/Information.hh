//
// Information.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  2 01:24:15 2014 alexis mestag
// Last update Sun Jun 21 00:04:42 2015 alexis mestag
//

#ifndef			__INFORMATION_HH__
# define		__INFORMATION_HH__

# include		<memory>
# include		"Entities/Unit.hh"
# include		"Utils/ISerializable.hh"

# include		<odb/core.hxx>

class			Information : public ISerializable
{
  friend class		Alert;
  friend class		Reading;
  friend class		odb::access;

private:
  std::shared_ptr<Unit const>	_unit;
  double			_value;

private:
  Information() = default;

public:
  Information(std::shared_ptr<Unit const> unit, double const value);
  Information(Information const &rhs) = default;

  Information		&operator=(Information const &rhs) = default;

  ~Information() = default;

public:
  bool				operator==(Information const &rhs) const;
  bool				operator!=(Information const &rhs) const;
  
public:
  double			getValue() const;
  void				setValue(double const value);

  Unit const			&getUnit() const;
  void				setUnit(Unit const &unit);
  void				setUnit(std::shared_ptr<Unit const> unit);

public:
  virtual void			serialize(Json::Value &json) const override;
};

# ifdef	ODB_COMPILER
#  pragma db value(Information)
#  pragma db member(Information::_unit) not_null
#  pragma db member(Information::_value)
# endif

#endif
