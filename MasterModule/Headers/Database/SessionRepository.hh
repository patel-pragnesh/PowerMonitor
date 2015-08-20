//
// SessionRepository.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb 23 01:19:03 2015 alexis mestag
// Last update Mon May  4 05:10:23 2015 alexis mestag
//

#ifndef			__SESSIONREPOSITORY_HH__
# define		__SESSIONREPOSITORY_HH__

# include		"Database/Repository.hpp"
# include		"Entities/Session-odb.hxx"

class			SessionRepository : public Repository<Session>
{
public:
  SessionRepository() = delete;
  SessionRepository(SessionRepository const &rhs) = delete;
  SessionRepository	&operator=(SessionRepository const &rhs) = delete;

  SessionRepository(Database &database);
  ~SessionRepository() = default;

public:
  Repository<Session>::pointer_type	getByToken(Session::token_type const &token);
};

#endif
