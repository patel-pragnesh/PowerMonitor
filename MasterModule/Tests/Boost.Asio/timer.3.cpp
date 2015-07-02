//
// timer.3.cpp for timer.3 in /home/mestag_a/Documents/Projets/EIP/MasterModule/Tests/Boost.Asio
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Jan 25 03:33:55 2015 alexis mestag
// Last update Sun Jan 25 04:04:07 2015 alexis mestag
//

#include	<iostream>
#include	<boost/asio.hpp>
#include	<boost/bind.hpp>
#include	<boost/date_time/posix_time/posix_time.hpp>

void		print(boost::system::error_code const &,
		      boost::asio::deadline_timer *t, int *count) {
  if (*count < 5) {
    std::cout << *count << std::endl;
    (*count)++;
    t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
    t->async_wait(boost::bind(&print,
			      boost::asio::placeholders::error,
			      t, count));
  }
}

int		main() {
  boost::asio::io_service io;
  boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
  int		count = 0;

  t.async_wait(boost::bind(&print,
			   boost::asio::placeholders::error,
			   &t, &count));
  io.run();
  std::cout << "Count: " << count << std::endl;
  return (0);
}
