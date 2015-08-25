//
// main.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Nov 29 00:37:51 2014 alexis mestag
// Last update Tue Aug 25 03:11:05 2015 alexis mestag
//

#include	<iostream>
#include	<boost/asio.hpp>

#include	"Database/Database.hh"
// #include	"Network/DistantServerConnector.hh"
#include	"Network/SlaveModuleServer.hh"
#include	"Network/UIHandler.hh"

int	main() {
  try {
    boost::asio::io_service	ios;
    boost::asio::signal_set	signals(ios);

    // DistantServerConnector	dsConnector(ios, "127.0.0.1", "4243");

    Database			db("powermonitor", "powermonitor", "powermonitor");
    SlaveModuleServer		smServer(ios, "0.0.0.0", "4244", db);
    UIHandler			uiHandler(ios, "0.0.0.0", "4242", db);

    signals.add(SIGINT);
    signals.add(SIGTERM);
    signals.add(SIGQUIT);
    signals.async_wait([&](boost::system::error_code const &, int) {
	smServer.stop();
	uiHandler.stop();	
      });

    ios.run();
  }
  catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  return (0);
}
