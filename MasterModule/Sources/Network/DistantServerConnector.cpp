//
// DistantServerConnector.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu May 28 15:11:14 2015 alexis mestag
// Last update Fri Jun 12 02:26:39 2015 alexis mestag
//

#include	<fstab.h>
#include	<iostream>
#include	"Network/DistantServerConnector.hh"
#include	"Utils/Bytes.hpp"
#include	"Utils/JsonValidator.hh"

DistantServerConnector::DistantServerConnector(boost::asio::io_service &ios,
					       std::string const &address,
					       std::string const &port) :
  AbstractConnection(ios),
  _ios(ios),
  _address(address), _port(port) {
  this->connect();
}

void		DistantServerConnector::connect() {
  tcp::resolver			resolver(_ios);
  tcp::resolver::query		query(_address, _port);
  tcp::resolver::iterator	endpoint_it = resolver.resolve(query);
  
  AbstractConnection::connect(endpoint_it,
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

      if (ok(received)) {
	// Read distant session token
	std::string	distantToken = received["session"]["dToken"].asString();

	// Find associated RequestHandler (if not any, create one)
	auto				it = _handlers.find(distantToken);
	std::shared_ptr<RequestHandler>	rh_ptr;

	if (it != _handlers.end()) {
	  rh_ptr = it->second;
	} else {
	  //rh_ptr = new RequestHandler();
	  _handlers[distantToken] = rh_ptr;
	}

	// handle the request
	Json::Value	response;
	rh_ptr->handle(received, response);

	// Reinsert the distant token
	response["session"]["dToken"] = distantToken;
	
	// send the response
	this->send(response, [this](boost::system::error_code const &ec, std::size_t) {
	    if (!ec) {
	      this->receiveRequests();
	    }
	  });
      }
    });
}

