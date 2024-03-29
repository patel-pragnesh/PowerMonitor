//
// DistantServerConnector.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu May 28 15:11:14 2015 alexis mestag
// Last update Fri Aug 28 01:46:58 2015 alexis mestag
//

#include	<fstab.h>
#include	<iostream>
#include	<json/reader.h>
#include	"Network/DistantServerConnector.hh"
#include	"Utils/Bytes.hpp"
#include	"Utils/JsonValidator.hh"

using	boost::asio::ip::tcp;

DistantServerConnector::DistantServerConnector(boost::asio::io_service &ios,
					       std::string const &address,
					       std::string const &port,
					       Database &database) :
  _ios(ios), _socket(ios),
  _address(address), _port(port),
  _database(database) {
  Json::StreamWriterBuilder	builder;
  
  builder.settings_["commentStyle"] = "None";
  builder.settings_["indentation"] = "";
  _jsonWriter.reset(builder.newStreamWriter());
  this->connect();
  }

void		DistantServerConnector::connect() {
  tcp::resolver			resolver(_ios);
  tcp::resolver::query		query(_address, _port);
  tcp::resolver::iterator	endpoint_it = resolver.resolve(query);
  
  boost::asio::async_connect(_socket,
			     endpoint_it,
			     [this](boost::system::error_code const &ec, tcp::resolver::iterator) {
			       if (!ec) {
				 std::cout << "Connected to distant server" << std::endl;
				 /* Register to the distant server */
				 this->sendUUID();
			       }
			     });
}

void		DistantServerConnector::sendUUID() {
  struct fstab	*entry = getfsfile("/");

  if (entry) {
    std::string	uuid(entry->fs_spec + 5); // +5 to get rid of "UUID="
    Json::Value request;

    request["cmd"] = "connect";
    request["id"] = uuid;
    
    this->send(request, [this](boost::system::error_code const &ec, std::size_t) {
	if (!ec) {
	  std::cout << "UUID sent to distant server" << std::endl;
	  this->recv([this](Json::Value const &response) {
	      std::cout << "Distant server sent :" << response.toStyledString();
	      // Study response
	      // if OK
	      //    read for requests
	      JsonValidator	ok = {
		{"returnCode", [](Json::Value const &v) -> bool {
		    return (v.isUInt64() && v.asUInt64() == 0);
		  }
		}
	      };

	      if (ok(response)) {
		this->receiveRequests();
	      }
	    });
	}
      });
  }

  endfsent();
}

void		DistantServerConnector::receiveRequests() {
  this->recv([this](Json::Value const &received) {
      JsonValidator	ok = {
	{"session", {
	    {"dToken", &JsonValidator::isNonEmptyString}
	  }
	}
      };

      _logger.out() << "Request : " << received.toStyledString() << std::endl;
      if (ok(received)) {
	// Should always be a session object (since distant server adds a dToken every time)
	Json::Value const	&session = received["session"];
	// Read distant session token
	std::string		dToken = session["dToken"].asString();

	std::shared_ptr<RequestHandler>	rh_ptr;
	if (session.isMember("token")) {
	  std::string const	token = session["token"].asString();
	  auto			it = _handlers.find(token);

	  if (it != _handlers.end()) {
	    rh_ptr = it->second;
	    _handlers.erase(it);
	  } else {
	    _logger.err() << "Warning: handler not found for session " << token << std::endl;
	  }
	}
	if (!rh_ptr) {
	  rh_ptr = std::make_shared<RequestHandler>(_database, _logger);
	}

	Json::Value		response;

	rh_ptr->handle(received, response);

	// Reinsert the distant token
	response["session"]["dToken"] = dToken;

	if (response["session"].isMember("token")) {
	  _handlers.insert(std::make_pair(response["session"]["token"].asString(), rh_ptr));
	}

	// send the response
	_logger.out() << "-> Response: " << response.toStyledString() << std::endl;
	this->send(response, [this](boost::system::error_code const &ec, std::size_t) {
	    if (!ec) {
	      this->receiveRequests();
	    }
	  });
      }
    });
}

void			DistantServerConnector::send(Json::Value const &toSend, sendHandler handler) {
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

void			DistantServerConnector::recv(recvHandler handler) {
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
