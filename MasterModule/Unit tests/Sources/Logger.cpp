//
// Logger.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule/Unit tests/c++
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Apr 15 16:39:10 2015 alexis mestag
// Last update Wed Apr 15 17:05:01 2015 alexis mestag
//

#include		<iostream>

#include		"Logger.hh"

Logger::Logger() :
  _out(std::cout), _err(std::cerr) {
}

void			Logger::setHeader(std::string const &header) {
  _header = header;
}

std::ostream		&Logger::log(std::ostream &os) {
  os << _header;
  return (os);
}

std::ostream		&Logger::out() {
  return (this->log(_out));
}

std::ostream		&Logger::err() {
  return (this->log(_err));
}
