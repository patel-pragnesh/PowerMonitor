//
// Session.hh for PowerMonitor in /home/mestag_a/Documents/Projets/ODB
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon May  4 03:04:02 2015 alexis mestag
// Last update Sat Jun 20 21:34:26 2015 alexis mestag
//

#ifndef			__SESSION_HH__
# define		__SESSION_HH__

# include		<array>
# include		<memory>

# include		<odb/core.hxx>

# include		"Entities/Entity.hh"
# include		"Entities/User.hh"

class				Session : public Entity
{
  friend class			odb::access;

public:
  using token_type		= std::array<unsigned char, 32>;
  
private:
  std::shared_ptr<User>		_user;
  token_type			_token;

private:
  Session() = default;  

public:
  Session(std::shared_ptr<User> const &user);
  Session(std::shared_ptr<User> &&user);
  Session(Session const &rhs) = delete;
  Session			&operator=(Session const &rhs) = delete;

  ~Session() = default;

public:
  void				generateToken();

  std::shared_ptr<User>		getUser();
  token_type const		&getToken() const;

  virtual void			serialize(Json::Value &json) const override;
};

# ifdef	ODB_COMPILER
#  pragma db object(Session)
#  pragma db member(Session::_user)
#  pragma db member(Session::_token) type("BINARY(32)")
# endif

#endif
