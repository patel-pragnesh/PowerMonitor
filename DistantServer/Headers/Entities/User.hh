//
// User.hh for Test in /home/mestag_a/Documents/Projets/ODB
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun May  3 22:53:09 2015 alexis mestag
// Last update Thu Jul  9 22:43:43 2015 alexis mestag
//

#ifndef			__USER_HH__
# define		__USER_HH__

# include		<array>
# include		<memory>
# include		<string>

# include		<odb/core.hxx>

# include		"Entities/Entity.hh"
# include		"Entities/MasterModule.hh"

class			User : public Entity
{
  friend class		odb::access;

private:
  std::string			_email;
  std::shared_ptr<MasterModule>	_module;

private:
  User() = default;
  
public:
  User(std::string const &email);
  User(std::string &&email);
  User(User const &rhs) = delete;
  User			&operator=(User const &rhs) = delete;

  ~User() = default;

public:
  std::string const	&getEmail() const;
  void			setEmail(std::string const &email);
  void			setEmail(std::string &&email);

  std::shared_ptr<MasterModule const>	getModule() const;
  void					setModule(std::shared_ptr<MasterModule> module);
  
  virtual void		serialize(Json::Value &json) const override;
};

# ifdef	ODB_COMPILER
#  pragma db object(User)
#  pragma db member(User::_email)
#  pragma db member(User::_module) not_null
# endif

#endif
