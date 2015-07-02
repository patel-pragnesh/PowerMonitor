//
// daytime.5.cpp for daytime.5 in /home/mestag_a/Documents/Projets/EIP/MasterModule/Tests/Boost.Asio
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Jan 25 19:20:50 2015 alexis mestag
// Last update Sun Jan 25 19:59:40 2015 alexis mestag
//

#include	<chrono>
#include	<iostream>
#include	<boost/asio.hpp>

using		boost::asio::ip::udp;

std::string		makeDaytimeString() {
  std::chrono::system_clock::time_point	tp = std::chrono::system_clock::now();
  std::time_t tt = std::chrono::system_clock::to_time_t(tp);

  return (std::ctime(&tt));
}

int		main() {
  try {
    boost::asio::io_service	io;
    udp::socket			socket(io, udp::endpoint(udp::v4(), 13));

    std::array<char, 1>		recv_buf;
    udp::endpoint		remote_endpoint;
    boost::system::error_code	ec;
    boost::system::error_code	ignored_error;
    std::string			msg;
    
    while (1) {
      socket.receive_from(boost::asio::buffer(recv_buf),
			  remote_endpoint, 0, ec);

      if (ec && ec != boost::asio::error::message_size)
	throw boost::system::system_error(ec);

      msg = makeDaytimeString();

      socket.send_to(boost::asio::buffer(msg),
		     remote_endpoint, 0, ignored_error);
    }
  }
  catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  return (0);
}
