//
// SlaveModuleServer.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Aug 25 02:27:34 2015 alexis mestag
// Last update Tue Aug 25 03:10:16 2015 alexis mestag
//

#ifndef		__SLAVEMODULESERVER_HH__
# define	__SLAVEMODULESERVER_HH__

# include	"Database/Database.hh"
# include	"Network/Server.hpp"
# include	"Network/SlaveModuleConnection.hh"

class	SlaveModuleServer : public Server<SlaveModuleConnection>
{
private:
  Database	&_db;

public:
  SlaveModuleServer(boost::asio::io_service &ios,
		    std::string &&address, std::string &&port,
		    Database &db);

  virtual std::shared_ptr<AbstractConnection>	getNewConnection() override {
    return (this->_getNewConnection<Database &>(_db));
  }
};

#endif
