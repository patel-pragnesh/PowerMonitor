//
// UIHandler.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Jul  6 18:18:26 2015 alexis mestag
// Last update Mon Jul 13 21:20:01 2015 alexis mestag
//

#ifndef		__UIHANDLER_HH__
# define	__UIHANDLER_HH__

# include	"Database/Database.hh"
# include	"Network/Server.hpp"
# include	"Network/UIConnection.hh"

class	UIHandler : public Server<UIConnection>
{
private:
  Database	&_database;

public:
  UIHandler(boost::asio::io_service &ios,
	    std::string &&address, std::string &&port,
	    Database &db);

  virtual std::shared_ptr<AbstractConnection>	getNewConnection() override;
};

#endif
