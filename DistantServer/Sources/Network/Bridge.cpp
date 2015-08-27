//
// Bridge.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Aug 26 00:54:32 2015 alexis mestag
// Last update Thu Aug 27 03:14:38 2015 alexis mestag
//

#include	<algorithm>
#include	<functional>
#include	<limits>
#include	<random>
#include	"Network/Bridge.hh"
#include	"Network/MasterModuleConnection.hh"
#include	"Network/UIConnection.hh"
#include	"Utils/Bytes.hpp"

void		Bridge::run(std::shared_ptr<UIConnection> c) {
  c->recv([this, c](Json::Value const &request) {
      Json::UInt64	returnCode = 0;
      // Here, forward request to master module
      // Find it before ?
      std::cout << "Request from UI: " << request.toStyledString() << std::endl;
      c->searchUser(request);
      if (c->getUser()) {
	// std::cerr << "UIConnection => " << c->getUser()->getEmail() << std::endl;
	auto		mmConnectionIt = std::find_if(_modules.begin(), _modules.end(),
						      [c](std::shared_ptr<MasterModuleConnection> &mmc) -> bool {
							return (c->getUser()->getModule()->getUUID() ==
								mmc->getModule()->getUUID());
						      });
	if (mmConnectionIt != _modules.end()) {
	  std::cout << "Module found !" << std::endl;
	  token		dToken = this->generateToken();
	  Json::Value	modifiedRequest(request);
      
	  modifiedRequest["session"]["dToken"] = Bytes::hexEncode(dToken);
	  _tokenToUI.insert(std::make_pair(dToken, c));
	  (*mmConnectionIt)->send(modifiedRequest, [this, c](boost::system::error_code const &ec, std::size_t) {
	      if (!ec) {
		this->run(c);
	      }
	    });
	} else {
	  std::cerr << "Module not found" << std::endl;
	  returnCode = 2;
	}
      } else {
	std::cerr << "User not found" << std::endl;
	returnCode = 1;
      }

      if (returnCode) {
	Json::Value response; response["returnCode"] = returnCode;

	c->send(response, [this, c](boost::system::error_code const &ec, std::size_t) {
	    if (!ec) { this->run(c); }
	  });
      }
    });
}

void		Bridge::registerModule(std::shared_ptr<MasterModuleConnection> c) {
  _modules.push_back(c);
  std::cout << "MasterModule connection registered for module " << c->getModule()->getUUID() << std::endl;
  this->run(c);
}

void		Bridge::run(std::shared_ptr<MasterModuleConnection> c) {
  c->recv([this, c](Json::Value const &json) {
      bool	dCommand = false;

      if (dCommand) {
	std::cerr << "Warning: DistantServer commands handling is not implemented yet" << std::endl;
      } else {
	std::string	dTokenString = json["session"]["dToken"].asString();

	if (dTokenString.empty()) {
	  std::cerr << "Warning: dToken is empty" << std::endl;
	} else {
	  token		dToken; Bytes::hexDecode(dTokenString, dToken);
	  auto		ui = _tokenToUI.find(dToken);

	  if (ui != _tokenToUI.end()) {
	    ui->second->send(json, [this, c](boost::system::error_code const &ec, std::size_t) {
		if (!ec) {
		  this->run(c);
		}
	      });
	  } else {
	    std::cerr << "Warning: no UI found for token " << dTokenString << std::endl;
	  }
	}
      }
    });
}

Bridge::token	Bridge::generateToken() {
  std::random_device					gen;
  std::uniform_int_distribution<token::value_type>	dist(std::numeric_limits<token::value_type>::min(),
							     std::numeric_limits<token::value_type>::max());
  token							ret;

  std::generate(ret.begin(), ret.end(), std::bind(dist, std::ref(gen)));
  return (ret);
}
