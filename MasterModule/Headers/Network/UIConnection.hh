//
// UIConnection.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Aug 25 01:38:40 2015 alexis mestag
// Last update Tue Aug 25 01:44:45 2015 alexis mestag
//

#ifndef		__UICONNECTION_HH__
# define	__UICONNECTION_HH__

# include	"Network/JsonConnection.hh"
# include	"Network/RequestHandler.hh"
# include	"Utils/Logger.hh"

class		UIConnection : public JsonConnection
{
private:
  Logger		_logger;
  RequestHandler	_requestHandler;

public:
  explicit UIConnection(boost::asio::ip::tcp::socket socket,
			ConnectionManager &connectionManager,
			Database &db);

  virtual void	start() override;
};

#endif
