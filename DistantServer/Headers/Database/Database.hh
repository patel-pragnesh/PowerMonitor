//
// Database.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Jan 19 00:50:06 2015 alexis mestag
// Last update Thu Apr 23 00:50:12 2015 alexis mestag
//

#ifndef			__DATABASE_HH__
# define		__DATABASE_HH__

# include		<memory>
# include		<string>

# include		<odb/database.hxx>
# include		<odb/session.hxx>

class			Database
{
private:
  typedef odb::database		type;

public:
  typedef unsigned long			id_type;
  typedef odb::transaction		transaction_type;

  template<typename T> using query_type		= odb::query<T>;
  template<typename T> using result_type	= odb::result<T>;
  template<typename T> using object_traits	= odb::object_traits<T>;

private:
  std::unique_ptr<type>	_database;
  odb::session		_session;

public:
  Database() = delete;
  Database(Database const &rhs) = delete;

  Database		operator=(Database const &rhs) = delete;

  Database(std::string const &user,
	   std::string const &password,
	   std::string const &database);
  ~Database() = default;

public:
  void						createSchema();
  transaction_type				*getTransaction();

  template<typename T>
  typename object_traits<T>::pointer_type	find(typename object_traits<T>::id_type const &id) {
    return (_database->find<T>(id));
  }
  
  template<typename T>
  result_type<T>				query() {
    return (_database->query<T>());
  }
  
  template<typename T>
  result_type<T>				query(query_type<T> const &query) {
    return (_database->query<T>(query));
  }

  template<typename T>
  T						query_value(query_type<T> const &query) {
    return (_database->query_value<T>(query));
  }
  
  template<typename T>
  typename object_traits<T>::id_type		persist(T &e) {
    return (_database->persist(e));
  }

  template<typename T>
  void						update(T const &e) {
    _database->update(e);
  }

  template<typename T>
  void						erase(T const &e) {
    _database->erase(e);
  }
};

#endif
