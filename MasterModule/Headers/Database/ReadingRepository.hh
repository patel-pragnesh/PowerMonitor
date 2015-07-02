//
// ReadingRepository.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Jun 20 22:52:20 2015 alexis mestag
// Last update Sat Jun 20 23:42:10 2015 alexis mestag
//

#ifndef		__READINGREPOSITORY_HH__
# define	__READINGREPOSITORY_HH__

# include	"Database/Repository.hpp"
# include	"Entities/Reading-odb.hxx"

class	ReadingRepository : public Repository<Reading>
{
public:
  ReadingRepository() = delete;
  ReadingRepository(ReadingRepository const &rhs) = delete;
  ReadingRepository	operator=(ReadingRepository const &rhs) = delete;

  ReadingRepository(Database &database);
  ~ReadingRepository() = default;

public:
  Repository<Reading>::result_type	getBetween(std::shared_ptr<SlaveModule const> const &module,
						   std::shared_ptr<Unit const> const &unit,
						   Time::Point const &beg, Time::Point const &end);
};

#endif
