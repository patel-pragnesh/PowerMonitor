//
// SlaveModuleConnection.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Aug 25 02:32:05 2015 alexis mestag
// Last update Tue Aug 25 03:07:27 2015 alexis mestag
//

#ifndef		__SLAVEMODULECONNECTION_HH__
# define	__SLAVEMODULECONNECTION_HH__

# include	"Database/Database.hh"
# include	"Network/AbstractConnection.hh"

class	SlaveModuleConnection : public AbstractConnection
{
private:
  Database	&_db;

public:
  explicit SlaveModuleConnection(boost::asio::ip::tcp::socket socket,
				 ConnectionManager &connectionManager,
				 Database &db);

  virtual void	start() override {
    // Implement slave module connection behaviour here
  }
};

#endif
