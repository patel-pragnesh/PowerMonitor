//
// MasterModuleConnection.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 21:25:46 2015 alexis mestag
// Last update Thu Jul  9 22:21:55 2015 alexis mestag
//

#include	<iostream>
#include	<json/reader.h>
#include	"Network/MasterModuleConnection.hh"
#include	"Utils/Bytes.hpp"

MasterModuleConnection::MasterModuleConnection(boost::asio::ip::tcp::socket socket,
					       ConnectionManager &connectionManager,
					       Database &database) :
  AbstractConnection(std::move(socket), connectionManager),
  _requestHandler(database) {
  Json::StreamWriterBuilder	builder;

  builder.settings_["commentStyle"] = "None";
  builder.settings_["indentation"] = "";
  _jsonWriter.reset(builder.newStreamWriter());
}

void		MasterModuleConnection::start() {
  this->recv([this](Json::Value const &json) {
      this->handle(json);
    });
}

void			MasterModuleConnection::handle(Json::Value const &json) {
  Json::Value		response;

  std::cout << "Received: " << json.toStyledString();
  _requestHandler(json, response);
  this->send(response, [this](boost::system::error_code const &ec, std::size_t) {
      if (!ec) {
	this->start();
      }
    });
}

void			MasterModuleConnection::send(Json::Value const &toSend, sendHandler const &handler) {
  std::ostringstream            oss;

  _jsonWriter->write(toSend, &oss);

  std::string                                   str = oss.str();
  int                                           size = Bytes::swap<int>(str.size());
  std::vector<boost::asio::const_buffer>        buffers = {
    boost::asio::buffer(&size, sizeof(size)),
    boost::asio::buffer(str)
  };

  boost::asio::async_write(this->socket(), buffers, handler);
}

void			MasterModuleConnection::recv(recvHandler const &handler) {
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
      boost::asio::async_read(this->socket(), boost::asio::buffer(_buffer, _sizeToRead),
			      onBufferRead);
    }
  };
  boost::asio::async_read(this->socket(), boost::asio::buffer(&_sizeToRead, sizeof(_sizeToRead)), onHeaderRead);
}
