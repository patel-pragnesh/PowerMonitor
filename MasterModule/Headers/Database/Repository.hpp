//
// Repository.hpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Feb  1 18:54:56 2015 alexis mestag
// Last update Thu Apr 23 00:51:38 2015 alexis mestag
//

#ifndef			__REPOSITORY_HPP__
# define		__REPOSITORY_HPP__

# include		<type_traits>
# include		"Database/Database.hh"
# include		"Entities/Entity.hh"

template<typename T>
class			Repository
{
  // static_assert(std::is_base_of<Entity, T>::value, "T must be a descendant of Entity");
  // This assert doesn't work anymore for ODB view structures

public:
  using object_traits	= Database::object_traits<T>;
  using id_type		= typename object_traits::id_type;
  using pointer_type	= typename object_traits::pointer_type;
  using query_type	= Database::query_type<T>;
  using result_type	= Database::result_type<T>;

protected:
  Database		&_database;
  
public:
  Repository() = delete;
  Repository(Repository const &rhs) = delete;
  Repository		&operator=(Repository const &rhs) = delete;

  Repository(Database &database) : _database(database) {}
  virtual ~Repository() = default;
  
public:
  pointer_type		getById(id_type const &id) {
    return (_database.find<T>(id));
  }

  result_type		getAll() {
    return (_database.query<T>());
  }

  id_type		persist(T &e) {
    return (_database.persist(e));
  }

  void			update(T const &e) {
    _database.update(e);
  }

  void			erase(T const &e) {
    _database.erase(e);
  }
};

#endif
