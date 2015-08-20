//
// Alert.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Dec  2 00:33:41 2014 alexis mestag
// Last update Sun Apr 12 23:04:44 2015 alexis mestag
//

#ifndef			__ALERT_HH__
# define		__ALERT_HH__

# include		<memory>
# include		<set>
# include		<odb/core.hxx>
# include		"Entities/Entity.hh"
# include		"Entities/Information.hh"
# include		"Entities/Profile.hh"
# include		"Entities/User.hh"

class			Alert : public Entity
{
  friend class		odb::access;

public:
  typedef std::set<std::shared_ptr<User>>	Users;

private:
  Information				_information;
  Users					_users;
  std::shared_ptr<Profile>		_profile;

private:
  Alert() = default;

public:
  Alert(Information &&information, std::shared_ptr<Profile> const &profile);
  Alert(Alert const &rhs) = default;

  Alert			&operator=(Alert const &rhs) = default;

  ~Alert() = default;

public:
  bool			operator==(Alert const &rhs) const;
  bool			operator!=(Alert const &rhs) const;
  
public:
  Information const	&getInformation() const;
  void			setInformation(Information const &information);

  void			setUnit(std::shared_ptr<Unit const> const &unit);
  void			setValue(double const value);
  
  Users const		&getUsers() const;
  void			setUsers(Users const &users);
  void			addUser(Users::value_type const &user);
  void			removeUser(Users::value_type const &rhs);

public:
  virtual void		serialize(Json::Value &json) const override;
};

# ifdef ODB_COMPILER
#  pragma db object(Alert)
#  pragma db member(Alert::_information)
#  pragma db member(Alert::_users)
#  pragma db member(Alert::_profile)
# endif


#endif
