//
// AlertRepository.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Apr 14 15:16:05 2015 alexis mestag
// Last update Tue Apr 14 15:23:12 2015 alexis mestag
//

#ifndef			__ALERTREPOSITORY_HH__
# define		__ALERTREPOSITORY_HH__

# include		"Database/Repository.hpp"
# include		"Entities/Alert-odb.hxx"
# include		"Entities/Profile-odb.hxx"

class			AlertRepository : public Repository<Alert>
{
public:
  AlertRepository() = delete;
  AlertRepository(AlertRepository const &rhs) = delete;
  AlertRepository	&operator=(AlertRepository const &rhs) = delete;

  AlertRepository(Database &database);
  ~AlertRepository() = default;

public:
  Repository<Alert>::result_type	getByProfile(Profile const &profile);
};

#endif
