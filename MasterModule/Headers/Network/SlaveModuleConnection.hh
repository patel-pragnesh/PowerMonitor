//
// SlaveModuleConnection.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Aug 25 02:32:05 2015 alexis mestag
// Last update Tue Aug 25 02:35:04 2015 alexis mestag
//

#ifndef		__SLAVEMODULECONNECTION_HH__
# define	__SLAVEMODULECONNECTION_HH__

# include	"Network/AbstractConnection.hh"

class	SlaveModuleConnection : public AbstractConnection
{
public:
  explicit SlaveModuleConnection(boost::asio::ip::tcp::socket socket,
				 ConnectionManager &connectionManager);

  virtual void	start() override {
    // Implement slave module connection behaviour here
  }
};

#endif
