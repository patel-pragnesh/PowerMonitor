//
// UIHandler.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue May 26 22:19:42 2015 alexis mestag
// Last update Tue Aug 25 02:01:49 2015 alexis mestag
//

#ifndef		__UIHANDLER_HH__
# define	__UIHANDLER_HH__

# include	<string>
# include	<boost/asio.hpp>

# include	"Database/Database.hh"
# include	"Network/Server.hpp"
# include	"Network/UIConnection.hh"

class	UIHandler : public Server<UIConnection>
{
private:
  Database		&_db;

public:
  UIHandler(boost::asio::io_service &ios,
	    std::string &&address, std::string &&port,
	    Database &db);

  virtual std::shared_ptr<AbstractConnection>	getNewConnection() override {
    return (this->_getNewConnection<Database &>(_db));
  }
};

#endif
