//
// Connection.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Jan 28 02:17:58 2015 alexis mestag
// Last update Thu Apr 23 01:20:24 2015 alexis mestag
//

#include		<iostream>
#include		<vector>
#include		<json/reader.h>
#include		<json/writer.h>
#include		"Network/Connection.hh"
#include		"Network/ConnectionManager.hh"
#include		"Utils/Byte.hh"

Connection::Connection(boost::asio::ip::tcp::socket socket,
		       ConnectionManager &connectionManager,
		       Database &database) :
  _socket(std::move(socket)), _connectionManager(connectionManager), _requestHandler(database, _logger) {
}

void			Connection::start() {
  this->read();
}

void			Connection::stop() {
  _logger.out() << "Connection closed" << std::endl;
  _requestHandler.persistSession();
  _socket.close();
}

void			Connection::read() {
  auto			onBufferRead = [this](boost::system::error_code const &ec, std::size_t bytes_transferred) {
    if (!ec) {
      Json::Reader	reader;

      _logger.out() << "Received " << bytes_transferred << std::endl;
      if (reader.parse(_buffer.data(), _buffer.data() + bytes_transferred, _request)) {
	_logger.out() << "Request: " << _request.toStyledString() << std::endl; // std::endl already in StyledString but needed to flush the buffer
	_requestHandler.handle(_request, _response);
	this->write();
      } else {
	(_logger.err() << "Didn't receive JSON formatted text: ").write(_buffer.data(), bytes_transferred) << std::endl;
	this->read();
      }
    } else if (ec != boost::asio::error::operation_aborted) {
      _connectionManager.stop(this->shared_from_this());
    }
  };
  auto			onHeaderRead = [this, onBufferRead](boost::system::error_code const &ec, std::size_t) {
    if (!ec) {
      auto rawToRead = _toRead;
      _toRead = Byte::swap(_toRead); // Important !
      _logger.out() << "Will read " << _toRead << " (raw: " << rawToRead << ')' << std::endl;
      /* Sould answer an error code if is going to read more than _buffer.size() */
      boost::asio::async_read(_socket, boost::asio::buffer(_buffer, _toRead), onBufferRead);
    } else if (ec != boost::asio::error::operation_aborted) {
      _connectionManager.stop(this->shared_from_this());
    }
  };
  boost::asio::async_read(_socket, boost::asio::buffer(&_toRead, sizeof(_toRead)), onHeaderRead);
}

void			Connection::write() {
  std::ostringstream		oss;
  Json::StreamWriterBuilder	builder;

  // builder.cs_ = Json::StreamWriter::CommentStyle::None;
  // builder.indentation_ = "";
  builder.settings_["commentStyle"] = "None";
  builder.settings_["indentation"] = "";
  std::shared_ptr<Json::StreamWriter>	writer(builder.newStreamWriter());

  writer->write(_response, &oss);

  std::string			str = oss.str();
  int				size = str.size(), rawSize = Byte::swap(size); // Important !

  _logger.out() << "Will send " << size << " (raw: " << rawSize << ")" << std::endl;
  std::vector<boost::asio::const_buffer>	buffers = {
    boost::asio::buffer(&rawSize, sizeof(rawSize)),
    boost::asio::buffer(str)
  };
  
  boost::asio::async_write(_socket, buffers, [this, rawSize](boost::system::error_code const &ec, std::size_t bytes_transferred) {
      if (!ec) {
	_logger.out() << "Sent " << bytes_transferred - sizeof(size) << std::endl;
	_logger.out() << "Response: " << _response.toStyledString() << std::endl;
	this->read();
      } else if (ec != boost::asio::error::operation_aborted) {
	_connectionManager.stop(this->shared_from_this());
      }
    });
}
