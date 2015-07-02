//
// time.4.cpp for time.4 in /home/mestag_a/Documents/Projets/EIP/MasterModule/Tests/Boost.Asio
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Jan 25 04:08:00 2015 alexis mestag
// Last update Sun Jan 25 04:20:33 2015 alexis mestag
//

#include	<iostream>
#include	<boost/asio.hpp>
#include	<boost/bind.hpp>
#include	<boost/date_time/posix_time/posix_time.hpp>

class		Printer
{
private:
  boost::asio::deadline_timer	_timer;
  int				_count;

public:
  Printer(boost::asio::io_service &io)
    : _timer(io, boost::posix_time::seconds(1)), _count(0) {
    _timer.async_wait(boost::bind(&Printer::print, this));
  }

  ~Printer() {
    std::cout << "Count: " << _count << std::endl;
  }

  void		print() {
    if (_count < 5) {
      std::cout << _count << std::endl;
      _count++;
      _timer.expires_at(_timer.expires_at() + boost::posix_time::seconds(1));
      _timer.async_wait(boost::bind(&Printer::print, this));
    }
  }
};

int		main() {
  boost::asio::io_service io;
  Printer	p(io);

  io.run();
  return (0);
}
