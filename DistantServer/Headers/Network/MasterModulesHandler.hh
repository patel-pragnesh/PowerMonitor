//
// MasterModulesHandler.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat May 30 18:39:03 2015 alexis mestag
// Last update Thu Jul  9 22:46:43 2015 alexis mestag
//

#ifndef		__MASTERMODULESHANDLER_HH__
# define	__MASTERMODULESHANDLER_HH__

# include	"Database/Database.hh"
# include	"Network/MasterModuleConnection.hh"
# include	"Network/Server.hpp"

using	boost::asio::ip::tcp;

class		MasterModulesHandler : public Server<MasterModuleConnection>
{
private:
  Database			_database;

public:
  MasterModulesHandler(boost::asio::io_service &ios,
		       std::string &&address, std::string &&port);

  virtual std::shared_ptr<AbstractConnection>	getNewConnection() override;
};

#endif
