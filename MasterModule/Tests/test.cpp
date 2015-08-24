//
// test.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb 23 22:00:09 2015 alexis mestag
// Last update Tue Aug 25 00:02:56 2015 alexis mestag
//

#include		<iostream>
#include		<memory>
#include		"Database/Database.hh"
#include		"Database/Repository.hpp"
#include		"Entities/Views/GlobalReading-odb.hxx"


int			main() {
  Database		db("powermonitor", "powermonitor", "powermonitor");
  Database::transaction_type	*t = db.getTransaction();
  Repository<GlobalReading>::query_type	q(Repository<GlobalReading>::query_type::tp.point == 1436299435);
  GlobalReading			result = db.query_value(q);

  std::cout << result.tp.getTimeSinceEpoch() << ": " << result.value << std::endl;
  
  delete t;
  return (0);
}
