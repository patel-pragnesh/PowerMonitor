//
// Database.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Jan 19 01:05:03 2015 alexis mestag
// Last update Mon Feb  2 01:52:54 2015 alexis mestag
//

#include		"Database/Database.hh"
#include		<odb/mysql/database.hxx>
#include		<odb/schema-catalog.hxx>

Database::Database(std::string const &user,
		   std::string const &password,
		   std::string const &database)
  : _database(new odb::mysql::database(user, password, database)) {
}

Database::transaction_type	*Database::getTransaction() {
  return (new transaction_type(_database->begin()));
}
