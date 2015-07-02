//
// daytime.2.cpp for daytime.2 in /home/mestag_a/Documents/Projets/EIP/MasterModule/Tests/Boost.Asio
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Jan 25 16:48:00 2015 alexis mestag
// Last update Sun Jan 25 18:20:27 2015 alexis mestag
//

#include	<chrono>
#include	<ctime>
#include	<iostream>
#include	<string>
#include	<boost/asio.hpp>

using		boost::asio::ip::tcp;

std::string	makeDaytimeString() {
  std::chrono::system_clock::time_point	tp = std::chrono::system_clock::now();
  std::time_t tt = std::chrono::system_clock::to_time_t(tp);

  return (std::ctime(&tt));
}

int		main() {
  try {
    boost::asio::io_service	io;
    tcp::acceptor		acceptor(io, tcp::endpoint(tcp::v4(), 13));

    while (1) {
      tcp::socket		socket(io);

      acceptor.accept(socket);
      std::string		msg = makeDaytimeString();

      boost::system::error_code	ignored_error;
      std::cout << "Sending: " << msg;
      boost::asio::write(socket, boost::asio::buffer(msg), ignored_error);
    }
  }
  catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return (1);
  }
  return (0);
}
