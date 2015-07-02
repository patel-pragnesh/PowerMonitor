//
// ReadingRepository.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Jun 20 22:51:43 2015 alexis mestag
// Last update Sat Jun 20 23:43:06 2015 alexis mestag
//

#include	"Database/ReadingRepository.hh"

ReadingRepository::ReadingRepository(Database &database) :
  Repository(database) {
}

Repository<Reading>::result_type	ReadingRepository::getBetween(std::shared_ptr<SlaveModule const> const &module,
								      std::shared_ptr<Unit const> const &unit,
								      Time::Point const &beg, Time::Point const &end) {
  Repository<Reading>::query_type	query(Repository<Reading>::query_type::module == module->getId() &&
					      Repository<Reading>::query_type::info.unit == unit->getId() &&
					      Repository<Reading>::query_type::tp.point >= beg.getTimeSinceEpoch() &&
					      Repository<Reading>::query_type::tp.point <= end.getTimeSinceEpoch());

  return (_database.query(query));
}

