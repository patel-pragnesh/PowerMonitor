//
// Bridge.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Aug 26 00:54:32 2015 alexis mestag
// Last update Wed Aug 26 03:34:09 2015 alexis mestag
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
      // Here, forward request to master module
      // Find it before ?
      c->searchUser(request);
      auto		mmConnectionIt = std::find_if(_modules.begin(), _modules.end(),
						      [c](std::shared_ptr<MasterModuleConnection> &mmc) -> bool {
							return (c->getUser()->getModule()->getUUID() == mmc->getModule()->getUUID());
						      });
      if (mmConnectionIt != _modules.end()) {
	token		dSession = this->generateToken();
	Json::Value	modifiedRequest(request);
      
	modifiedRequest["dSession"] = Bytes::hexEncode(dSession);
	_tokenToUI.insert(std::make_pair(dSession, c));
	(*mmConnectionIt)->send(request, [this, c](boost::system::error_code const &ec, std::size_t) {
	    if (!ec) {
	      this->run(c);
	    }
	  });
      }
      
      // this->run(c);
    });
}

void		Bridge::registerModule(std::shared_ptr<MasterModuleConnection> c) {
  _modules.push_back(c);
  this->run(c);
}

void		Bridge::run(std::shared_ptr<MasterModuleConnection> c) {
  c->recv([this, c](Json::Value const &json) {
      bool	dCommand = false;

      if (dCommand) {
	std::cerr << "Warning: DistantServer commands handling is not implemented yet" << std::endl;
      } else {
	std::string	dSessionString = json["dSession"].asString();

	if (dSessionString.empty()) {
	  std::cerr << "Warning: dSession is empty" << std::endl;
	} else {
	  token		dSession; Bytes::hexDecode(dSessionString, dSession);
	  auto		ui = _tokenToUI.find(dSession);

	  if (ui != _tokenToUI.end()) {
	    ui->second->send(json, [this, c](boost::system::error_code const &ec, std::size_t) {
		if (!ec) {
		  this->run(c);
		}
	      });
	  } else {
	    std::cerr << "Warning: UI not found for token " << dSessionString << std::endl;
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
