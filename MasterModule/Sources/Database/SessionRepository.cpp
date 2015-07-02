//
// SessionRepository.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb 23 01:22:22 2015 alexis mestag
// Last update Mon May  4 05:10:01 2015 alexis mestag
//

#include			"Database/SessionRepository.hh"

SessionRepository::SessionRepository(Database &database) :
  Repository<Session>(database) {
}

Repository<Session>::pointer_type	SessionRepository::getByToken(Session::token_type const &token) {
  Repository<Session>::pointer_type	ret = nullptr;
  Repository<Session>::query_type	query(Repository<Session>::query_type::token == token);
  Repository<Session>::result_type	result(_database.query(query));

  if (result.size()) {
    ret = result.begin().load();
  }
  return (ret);
}
