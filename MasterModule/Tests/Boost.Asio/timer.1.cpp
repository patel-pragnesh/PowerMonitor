//
// sync_timer.cpp for sync_timer in /home/mestag_a/Documents/Projets/EIP/MasterModule/Tests/Boost.Asio
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Jan 25 02:54:45 2015 alexis mestag
// Last update Sun Jan 25 03:02:40 2015 alexis mestag
//

#include	<iostream>
#include	<boost/asio.hpp>
#include	<boost/date_time/posix_time/posix_time.hpp>

int		main() {
  boost::asio::io_service io;
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));

  t.wait();
  std::cout << "Hello World !" << std::endl;
  return (0);
}
