//
// AbstractConnection.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Fri Jun 12 01:59:15 2015 alexis mestag
// Last update Fri Jun 12 02:22:29 2015 alexis mestag
//

#include	<sstream>
#include	<string>
#include	<vector>
#include	<json/reader.h>

#include	"Utils/Bytes.hpp"
#include	"Network/AbstractConnection.hh"

AbstractConnection::AbstractConnection(boost::asio::io_service &ios) :
  _socket(ios) {
  this->init();
}

AbstractConnection::AbstractConnection(tcp::socket &&socket) :
  _socket(std::move(socket)) {
  this->init();
}

void		AbstractConnection::init() {
  Json::StreamWriterBuilder     builder;

  builder.settings_["commentStyle"] = "None";
  builder.settings_["indentation"] = "";
  _jsonWriter.reset(builder.newStreamWriter());
}

void		AbstractConnection::connect(tcp::resolver::iterator endpoint_it, connectHandler const &handler) {
  boost::asio::async_connect(_socket, endpoint_it, handler);
}

void		AbstractConnection::send(Json::Value const &json, sendHandler const &handler) {
  std::ostringstream		oss;

  _jsonWriter->write(json, &oss);

  std::string					str = oss.str();
  int						size = Bytes::swap<int>(str.size());
  std::vector<boost::asio::const_buffer>	buffers = {
    boost::asio::buffer(&size, sizeof(size)),
    boost::asio::buffer(str)
  };

  boost::asio::async_write(_socket, buffers, handler);
}

void		AbstractConnection::recv(recvHandler const &handler) {
  auto		onBufferRead = [this, handler](boost::system::error_code const &ec, std::size_t bytes_transferred) {
    if (!ec) {
      Json::Value	response;
      Json::Reader	reader;

      if (reader.parse(_buffer.data(), _buffer.data() + bytes_transferred, response)) {
	handler(response);
      }
    }
  };
  auto		onHeaderRead = [this, onBufferRead](boost::system::error_code const &ec, std::size_t) {
    if (!ec) {
      _sizeToRead = Bytes::swap(_sizeToRead);
      boost::asio::async_read(_socket, boost::asio::buffer(_buffer, _sizeToRead),
			      onBufferRead);
    }
  };
  boost::asio::async_read(_socket, boost::asio::buffer(&_sizeToRead, sizeof(_sizeToRead)), onHeaderRead);
}
