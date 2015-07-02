//
// Connection.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 28 02:17:58 2015 alexis mestag
// Last update Tue Jun  2 09:51:27 2015 laurent ansel
//

#include		<iostream>
#include		<vector>
#include		<json/reader.h>
#include		"Network/Connection.hh"
#include		"Network/ConnectionManager.hh"
#include		"Utils/Bytes.hpp"

Connection::Connection(boost::asio::ip::tcp::socket socket,
		       ConnectionManager &connectionManager,
		       Database &db) :
  _socket(std::move(socket)),
  _connectionManager(connectionManager),
  _requestHandler(db, *this) {
  Json::StreamWriterBuilder	builder;

  builder.settings_["commentStyle"] = "None";
  builder.settings_["indentation"] = "";
  _jsonWriter.reset(builder.newStreamWriter());
}

void			Connection::start() {
  this->recv([this](Json::Value const &json) {
      this->handle(json);
    });
}

void			Connection::stop() {
  _socket.close();
}

void			Connection::handle(Json::Value const &json) {
  Json::Value		response;

  std::cout << "Received: " << json.toStyledString();
  _requestHandler(json, response);
  this->send(response, [this](boost::system::error_code const &ec, std::size_t) {
      if (!ec) {
	this->start();
      }
    });
}

void			Connection::send(Json::Value const &toSend, sendHandler const &handler) {
  std::ostringstream            oss;

  _jsonWriter->write(toSend, &oss);

  std::string                                   str = oss.str();
  int                                           size = Bytes::swap<int>(str.size());
  std::vector<boost::asio::const_buffer>        buffers = {
    boost::asio::buffer(&size, sizeof(size)),
    boost::asio::buffer(str)
  };

  boost::asio::async_write(_socket, buffers, handler);
}

void			Connection::recv(recvHandler const &handler) {
  auto          onBufferRead = [this, handler](boost::system::error_code const &ec, std::size_t bytes_transferred) {
    if (!ec) {
      Json::Value       received;
      Json::Reader      reader;

      if (reader.parse(_buffer.data(), _buffer.data() + bytes_transferred, received)) {
	handler(received);
      }
    }
  };
  auto          onHeaderRead = [this, onBufferRead](boost::system::error_code const &ec, std::size_t) {
    if (!ec) {
      _sizeToRead = Bytes::swap(_sizeToRead);
      boost::asio::async_read(_socket, boost::asio::buffer(_buffer, _sizeToRead),
			      onBufferRead);
    }
  };
  boost::asio::async_read(_socket, boost::asio::buffer(&_sizeToRead, sizeof(_sizeToRead)), onHeaderRead);
}
