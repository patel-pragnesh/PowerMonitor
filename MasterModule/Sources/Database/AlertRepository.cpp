//
// AlertRepository.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Apr 14 15:32:14 2015 alexis mestag
// Last update Tue Apr 14 15:37:52 2015 alexis mestag
//

#include			"Database/AlertRepository.hh"

AlertRepository::AlertRepository(Database &database) :
  Repository<Alert>(database) {
}

Repository<Alert>::result_type		AlertRepository::getByProfile(Profile const &profile) {
  Repository<Alert>::query_type		query(Repository<Alert>::query_type::profile == profile.getId());

  return (_database.query(query));
}
