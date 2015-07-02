//
// timer.5.cpp for timer.5 in /home/mestag_a/Documents/Projets/EIP/MasterModule/Tests/Boost.Asio
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Jan 25 04:26:33 2015 alexis mestag
// Last update Sun Jan 25 16:22:35 2015 alexis mestag
//

#include	<iostream>
#include	<boost/asio.hpp>
#include	<boost/bind.hpp>
#include	<boost/date_time/posix_time/posix_time.hpp>
#include	<boost/thread/thread.hpp>

class		Printer
{
private:
  boost::asio::io_service::strand	_strand;
  boost::asio::deadline_timer		_timer1;
  boost::asio::deadline_timer		_timer2;
  int					_count;

public:
  Printer(boost::asio::io_service &io)
    : _strand(io),
      _timer1(io, boost::posix_time::seconds(1)),
      _timer2(io, boost::posix_time::seconds(1)),
      _count(0) {
    _timer1.async_wait(_strand.wrap(boost::bind(&Printer::print1, this)));
    _timer2.async_wait(_strand.wrap(boost::bind(&Printer::print2, this)));
  }

  ~Printer() {
    std::cout << "Count: " << _count << std::endl;
  }

  void		print1() {
    if (_count < 10) {
      std::cout << "Timer 1: " << _count << std::endl;
      _count++;
      _timer1.expires_at(_timer1.expires_at() + boost::posix_time::seconds(1));
      _timer1.async_wait(_strand.wrap(boost::bind(&Printer::print1, this)));
    }
  }
  void		print2() {
    if (_count < 10) {
      std::cout << "Timer 2: " << _count << std::endl;
      _count++;
      _timer2.expires_at(_timer2.expires_at() + boost::posix_time::seconds(1));
      _timer2.async_wait(_strand.wrap(boost::bind(&Printer::print2, this)));
    }
  }
};

int		main() {
  boost::asio::io_service io;
  Printer	p(io);
  boost::thread t(boost::bind(&boost::asio::io_service::run, &io));

  io.run();
  t.join();
  return (0);
}
