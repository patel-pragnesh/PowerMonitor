//
// client.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Feb  7 02:36:51 2015 alexis mestag
// Last update Wed Apr 22 23:54:54 2015 alexis mestag
//

#include		<array>
#include		<iostream>
#include		<vector>
#include		<sstream>
#include		<json/reader.h>
#include		<json/writer.h>
#include		<boost/asio.hpp>

using			boost::asio::ip::tcp;

template<typename T>
static T		swapBytes(T value) {
  unsigned int		bytes = sizeof(T);
  int			byte;
  T			ret = 0;

  for (unsigned int offset = 0; offset < bytes; ++offset) {
    byte = (value & (0xff << 8 * (bytes - (offset + 1)))) >> (8 * (bytes - (offset + 1)));
    ret |= byte << (8 * offset);
  }
  return (ret);
}

int			main() {
  char			buffer[1024] = {0};
  std::streamsize	ssize;
  std::ostringstream	osstr;

  while (std::cin.good()) {
    osstr << buffer;
    std::cin.getline(buffer, sizeof(buffer) - 1);
    ssize = std::cin.gcount();
    if (ssize < (sizeof(buffer) - 1)) {
      buffer[ssize - 1] = '\n';
      buffer[ssize] = 0;
    }
  }

  boost::asio::io_service	io;
  tcp::resolver			resolver(io);
  tcp::resolver::query		query("0.0.0.0", "4242");
  tcp::resolver::iterator	endpoint_it = resolver.resolve(query);
  tcp::socket			socket(io);

  boost::asio::connect(socket, endpoint_it);

  std::string					str = osstr.str();
  unsigned int					size = str.size();

  std::cout << "Will write " << size;
  size = swapBytes(size);
  std::cout << ": raw(" << size << ")" << std::endl;
  std::vector<boost::asio::const_buffer>	buffers = {
    boost::asio::buffer(&size, sizeof(size)),
    boost::asio::buffer(str)
  };
  boost::asio::write(socket, buffers);

  //========
  
  boost::asio::read(socket, boost::asio::buffer(&size, sizeof(size)));
  std::cout << "Will read " << size;
  size = swapBytes(size);
  std::cout << ": raw(" << size << ")" << std::endl;
  char				*readBuf = new char[size];
  boost::asio::read(socket, boost::asio::buffer(readBuf, size));

  Json::Reader			reader;
  Json::Value			response;

  reader.parse(readBuf, readBuf + size - 1, response);

  Json::StreamWriterBuilder	builder;
  std::shared_ptr<Json::StreamWriter>	writer(builder.newStreamWriter());

  writer->write(response, &std::cout);
  std::cout << std::endl;
  return (0);
}
