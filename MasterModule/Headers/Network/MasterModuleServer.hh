//
// MasterModuleServer.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Jan 24 18:45:59 2015 alexis mestag
// Last update Tue Aug 25 01:28:59 2015 alexis mestag
//

#ifndef			__MASTERMODULESERVER_HH__
# define		__MASTERMODULESERVER_HH__

# include		<string>
# include		<boost/asio.hpp>
# include		"Database/Database.hh"
# include		"Network/Server.hpp"
# include		"Network/UIConnection.hh"

class			MasterModuleServer : public Server<UIConnection>
{
private:
  Database			&_database;

public:
  MasterModuleServer() = delete;
  MasterModuleServer(MasterModuleServer const &rhs) = delete;

  MasterModuleServer	&operator=(MasterModuleServer const &rhs) = delete;

  MasterModuleServer(boost::asio::io_service &ios,
		     std::string &&address, std::string &&port,
		     Database &db);
  ~MasterModuleServer() = default;

  virtual std::shared_ptr<AbstractConnection>	getNewConnection() override {
    return (this->_getNewConnection<Database &>(db));
  }
};

#endif
