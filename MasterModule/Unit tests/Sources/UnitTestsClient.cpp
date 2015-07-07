//
// UnitTestsClient.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule/Unit tests/c++
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Apr 14 17:57:21 2015 alexis mestag
// Last update Tue Jul  7 22:33:55 2015 alexis mestag
//

#include		<list>
#include		<memory>
#include		<sstream>

#include		<json/reader.h>
#include		<json/writer.h>

#include		"Tests/AlertTest.hh"
#include		"Tests/LoginTest.hh"
#include		"Tests/ModuleTest.hh"
#include		"Tests/TimeSlotTest.hh"
#include		"UnitTestsClient.hh"
#include		"UnitTest.hh"
#include		"Utils/Byte.hh"

UnitTestsClient::UnitTestsClient(std::string const &address, std::string const &port) :
  _socket(_ios) {
  tcp::resolver			resolver(_ios);
  tcp::resolver::query		query(address, port);
  tcp::resolver::iterator	endpoint_it = resolver.resolve(query);

  boost::asio::connect(_socket, endpoint_it);
}

void			UnitTestsClient::run() {
  std::list<std::shared_ptr<UnitTest>>	tests = {
    std::shared_ptr<UnitTest>(new LoginTest(*this)),
    std::shared_ptr<UnitTest>(new AlertTest(*this)),
    std::shared_ptr<UnitTest>(new TimeSlotTest(*this)),
    std::shared_ptr<UnitTest>(new ModuleTest(*this)),
  };
  bool			ret;

  _logger.out() << std::boolalpha;
  _logger.out() << "Starting tests" << std::endl;
  for (auto test: tests) {
    _logger.out() << "- " << test->getDescription() << std::endl;
    _logger.setHeader("  - ");
    ret = (*test)();
    _logger.setHeader("");
    _logger.out() << "  => Result: " << ret << std::endl;
  }
}

void			UnitTestsClient::send(Json::Value const &request) {
  std::ostringstream		oss;
  Json::StreamWriterBuilder	builder;

  builder.settings_["commentStyle"] = "None";
  builder.settings_["indentation"] = "";
  std::shared_ptr<Json::StreamWriter>	writer(builder.newStreamWriter());

  writer->write(request, &oss);

  std::string                   str = oss.str();
  int                           size = str.size(), rawSize = Byte::swap(size); // Important !

  std::vector<boost::asio::const_buffer>        buffers = {
    boost::asio::buffer(&rawSize, sizeof(rawSize)),
    boost::asio::buffer(str)
  };

  boost::asio::write(_socket, buffers);
}

void			UnitTestsClient::recv(Json::Value &response) {
  unsigned int		size;
  char			*readBuf;
  Json::Reader		reader;


  boost::asio::read(_socket, boost::asio::buffer(&size, sizeof(size)));
  size = Byte::swap(size);
  readBuf = new char[size];
  boost::asio::read(_socket, boost::asio::buffer(readBuf, size));
  response.clear();
  reader.parse(readBuf, readBuf + size - 1, response);
}

Logger			&UnitTestsClient::log() {
  return (_logger);
}
