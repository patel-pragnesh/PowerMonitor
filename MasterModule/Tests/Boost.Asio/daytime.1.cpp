//
// daytime.1.cpp for daytime.1 in /home/mestag_a/Documents/Projets/EIP/MasterModule/Tests/Boost.Asio
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Jan 25 16:22:57 2015 alexis mestag
// Last update Sun Jan 25 16:45:36 2015 alexis mestag
//

#include	<array>
#include	<iostream>
#include	<boost/asio.hpp>

using		boost::asio::ip::tcp;

int		main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <host>" << std::endl;
    return (1);
  }

  try {
    boost::asio::io_service	io;
    tcp::resolver		resolver(io);
    tcp::resolver::query	query(argv[1], "daytime");
    tcp::resolver::iterator	endpoint_it = resolver.resolve(query);
    tcp::socket			socket(io);

    boost::asio::connect(socket, endpoint_it);

    std::array<char, 128>	buf;
    size_t			len;
    boost::system::error_code	ec;

    while (!ec) {
      len = socket.read_some(boost::asio::buffer(buf), ec);

      if (ec && ec != boost::asio::error::eof) {
	throw boost::system::system_error(ec);
      }

      std::cout.write(buf.data(), len);
    }
  }
  catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return (2);
  }
  return (0);
}
