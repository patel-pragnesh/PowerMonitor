//
// main.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Nov 29 00:37:51 2014 alexis mestag
// Last update Sat May 30 18:52:45 2015 alexis mestag
//

#include	<iostream>
#include	<boost/asio.hpp>

#include	"Network/MasterModulesHandler.hh"

int	main() {
  try {
    boost::asio::io_service	ios;
    boost::asio::signal_set	signals(ios);
    MasterModulesHandler	mmHandler(ios, "0.0.0.0", "4243");

    signals.add(SIGINT);
    signals.add(SIGTERM);
    signals.add(SIGQUIT);
    signals.async_wait([&](boost::system::error_code const &, int) {
	mmHandler.stop();
      });

    ios.run();
  }
  catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  return (0);
}
