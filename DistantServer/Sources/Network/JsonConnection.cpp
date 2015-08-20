//
// JsonConnection.hh<Sources> for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Jul 11 16:58:15 2015 alexis mestag
// Last update Sat Jul 11 19:55:29 2015 alexis mestag
//

#include	<json/reader.h>
#include	"Network/JsonConnection.hh"
#include	"Utils/Bytes.hpp"

JsonConnection::JsonConnection(boost::asio::ip::tcp::socket socket,
			       ConnectionManager &connectionManager) :
  AbstractConnection(std::move(socket), connectionManager) {
  Json::StreamWriterBuilder	builder;

  builder.settings_["commentStyle"] = "None";
  builder.settings_["indentation"] = "";
  _jsonWriter.reset(builder.newStreamWriter());
}

void			JsonConnection::send(Json::Value const &toSend, sendHandler const &handler) {
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

void			JsonConnection::recv(recvHandler const &handler) {
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
