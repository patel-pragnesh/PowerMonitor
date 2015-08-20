//
// async_timer.cpp for async_timer in /home/mestag_a/Documents/Projets/EIP/MasterModule/Tests/Boost.Asio
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Jan 25 03:09:45 2015 alexis mestag
// Last update Sun Jan 25 03:27:38 2015 alexis mestag
//

#include	<iostream>
#include	<boost/asio.hpp>
#include	<boost/date_time/posix_time/posix_time.hpp>

void		print(boost::system::error_code const &) {
  std::cout << "Hello World !" << std::endl;
}

int		main() {
  boost::asio::io_service io;
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));

  t.async_wait(&print);
  io.run();
  return (0);
}
