//
// Logger.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar  3 20:10:47 2015 alexis mestag
// Last update Wed Mar  4 00:55:55 2015 alexis mestag
//

#include			"Utils/Logger.hh"

Logger::Logger() :
  _out(std::cout), _err(std::cerr) {
}

Logger::Logger(std::ostream &os) :
  _out(os), _err(os) {
}

Logger::Logger(std::ostream &out, std::ostream &err) :
  _out(out), _err(err) {
}

void			Logger::setHeader(std::string const &header) {
  _header= header;
}

std::ostream		&Logger::log(std::ostream &os) {
  time_t		t = clock::to_time_t(clock::now());
  std::string		time(ctime(&t));

  os << '[' << time.substr(0, time.size() - 1) << "]: ";
  if (!_header.empty()) {
    os << _header << ": ";
  }
  return (os);
}

std::ostream		&Logger::out() {
  return (this->log(_out));
}

std::ostream		&Logger::err() {
  return (this->log(_err));
}
