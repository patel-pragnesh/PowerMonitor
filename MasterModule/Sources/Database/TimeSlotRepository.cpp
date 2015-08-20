//
// TimeSlotRepository.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Apr 14 15:38:01 2015 alexis mestag
// Last update Tue Apr 14 15:38:18 2015 alexis mestag
//

#include			"Database/TimeSlotRepository.hh"

TimeSlotRepository::TimeSlotRepository(Database &database) :
  Repository<TimeSlot>(database) {
}

Repository<TimeSlot>::result_type	TimeSlotRepository::getByProfile(Profile const &profile) {
  Repository<TimeSlot>::query_type	query(Repository<TimeSlot>::query_type::profile == profile.getId());

  return (_database.query(query));
}
