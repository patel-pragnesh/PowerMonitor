//
// Entity.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Nov 29 00:17:39 2014 alexis mestag
// Last update Fri Jun  5 07:20:00 2015 laurent ansel
//

#ifndef			__ENTITY_HH__
# define		__ENTITY_HH__

# include		"Utils/ISerializable.hh"
# include		<odb/core.hxx>

# include		"Network/Connection.hh"

class			Entity : public ISerializable
{
  friend class		odb::access;

private:
  unsigned long		_id;
  Connection		*_network;

protected:
  Entity() = default;
  Entity(unsigned long id);
  Entity(Entity const &rhs) = default;

  Entity		&operator=(Entity const &rhs) = default;

public:
  virtual ~Entity() = default;

private:
  void			setId(unsigned long const id);

public:
  unsigned long		getId() const;

  Connection		&getNetwork() const;
  void			setNetwork(Connection *network);
  bool			isConnect() const;

public:
  virtual void		serialize(Json::Value &json) const override;
};

# ifdef	ODB_COMPILER
#  pragma db object(Entity) abstract
#  pragma db member(Entity::_id) id auto
#  pragma db member(Entity::_network) transient
# endif

#endif
