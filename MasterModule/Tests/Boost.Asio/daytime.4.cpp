//
// daytime.4.cpp for daytime.4 in /home/mestag_a/Documents/Projets/EIP/MasterModule/Tests/Boost.Asio
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Jan 25 18:53:49 2015 alexis mestag
// Last update Sun Jan 25 19:12:37 2015 alexis mestag
//

#include	<iostream>
#include	<boost/asio.hpp>

using		boost::asio::ip::udp;

int		main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <host>" << std::endl;
    return (1);
  }

  try {
    boost::asio::io_service	io;
    udp::resolver		resolver(io);
    udp::resolver::query	query(udp::v4(), argv[1], "daytime");
    udp::endpoint		receiver_endpoint = *resolver.resolve(query);
    udp::socket			socket(io);

    socket.open(udp::v4());
    std::array<char, 1>		buf = {0};
    socket.send_to(boost::asio::buffer(buf), receiver_endpoint);

    std::array<char, 128>	recv_buf;
    udp::endpoint		sender_endpoint;
    size_t			len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint);

    std::cout.write(recv_buf.data(), len);
  }
  catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return (2);
  }
  return (0);
}
