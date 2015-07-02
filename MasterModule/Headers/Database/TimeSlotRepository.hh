//
// TimeSlotRepository.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Apr 14 15:19:06 2015 alexis mestag
// Last update Tue Apr 14 15:23:17 2015 alexis mestag
//

#ifndef			__TIMESLOTREPOSITORY_HH__
# define		__TIMESLOTREPOSITORY_HH__

# include		"Database/Repository.hpp"
# include		"Entities/Profile-odb.hxx"
# include		"Entities/TimeSlot-odb.hxx"

class			TimeSlotRepository : public Repository<TimeSlot>
{
public:
  TimeSlotRepository() = delete;
  TimeSlotRepository(TimeSlotRepository const &rhs) = delete;
  TimeSlotRepository	&operator=(TimeSlotRepository const &rhs) = delete;

  TimeSlotRepository(Database &database);
  ~TimeSlotRepository() = default;

public:
  Repository<TimeSlot>::result_type	getByProfile(Profile const &profile);
};

#endif
