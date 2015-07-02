//
// Unit.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  2 00:46:19 2014 alexis mestag
// Last update Tue Feb 10 20:53:06 2015 alexis mestag
//

#ifndef			__UNIT_HH__
# define		__UNIT_HH__

# include		<string>
# include		"Entities/Entity.hh"

# include		<odb/core.hxx>

class			Unit : public Entity
{
  friend class		odb::access;

private:
  std::string		_name;
  std::string		_symbol;

private:
  Unit() = default;

public:
  Unit(Unit const &rhs) = delete;
  Unit(std::string const &name, std::string const &symbol);

  Unit			&operator=(Unit const &rhs) = delete;

  ~Unit() = default;

public:
  bool			operator==(Unit const &rhs) const;
  bool			operator!=(Unit const &rhs) const;
  
public:
  std::string const	&getName() const;
  void			setName(std::string const &name);

  std::string const	&getSymbol() const;
  void			setSymbol(std::string const &symbol);

public:
  virtual void		serialize(Json::Value &json) const override;
};

# ifdef	ODB_COMPILER
#  pragma db object(Unit)
#  pragma db member(Unit::_name)
#  pragma db member(Unit::_symbol)
# endif

#endif
