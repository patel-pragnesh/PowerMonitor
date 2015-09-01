//
// MasterModulesHandler.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat May 30 18:39:03 2015 alexis mestag
// Last update Wed Aug 26 02:59:43 2015 alexis mestag
//

#ifndef		__MASTERMODULESHANDLER_HH__
# define	__MASTERMODULESHANDLER_HH__

# include	"Database/Database.hh"
# include	"Network/MasterModuleConnection.hh"
# include	"Network/Server.hpp"

class		Bridge;

class		MasterModulesHandler : public Server<MasterModuleConnection>
{
private:
  Bridge			&_bridge;
  Database			&_database;

public:
  MasterModulesHandler(boost::asio::io_service &ios,
		       std::string &&address, std::string &&port,
		       Bridge &bridge, Database &db);

  virtual std::shared_ptr<AbstractConnection>	getNewConnection() override;
};

#endif
