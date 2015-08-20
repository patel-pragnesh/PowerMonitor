//
// User.hh for Test in /home/mestag_a/Documents/Projets/ODB
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun May  3 22:53:09 2015 alexis mestag
// Last update Mon May  4 05:01:54 2015 alexis mestag
//

#ifndef			__USER_HH__
# define		__USER_HH__

# include		<array>
# include		<string>

# include		<odb/core.hxx>

# include		"Entities/Entity.hh"

class			User : public Entity
{
  friend class		odb::access;

public:
  using	hash_type	= std::array<unsigned char, 32>;
  using salt_type	= hash_type;

private:
  std::string		_name;
  std::string		_surname;
  std::string		_email;
  hash_type		_hash;
  salt_type		_salt;

private:
  User() = default;
  
public:
  User(std::string const &name,
       std::string const &surname,
       std::string const &email);
  User(std::string &&name,
       std::string &&surname,
       std::string &&email);
  User(User const &rhs) = delete;
  User			&operator=(User const &rhs) = delete;

  ~User() = default;

public:
  std::string const	&getName() const;
  void			setName(std::string const &name);
  void			setName(std::string &&name);

  std::string const	&getSurname() const;
  void			setSurname(std::string const &surname);
  void			setSurname(std::string &&surname);

  std::string const	&getEmail() const;
  void			setEmail(std::string const &email);
  void			setEmail(std::string &&email);

  hash_type const	&getHash() const;
  salt_type const	&getSalt() const;
  void			setPassword(std::string const &password);

  virtual void		serialize(Json::Value &json) const override;
};

# ifdef	ODB_COMPILER
#  pragma db object(User)
#  pragma db member(User::_name)
#  pragma db member(User::_surname)
#  pragma db member(User::_email)
#  pragma db member(User::_hash) type("BINARY(32)")
#  pragma db member(User::_salt) type("BINARY(32)")
# endif

#endif
