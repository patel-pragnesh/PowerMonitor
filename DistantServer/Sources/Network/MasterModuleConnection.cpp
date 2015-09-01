//
// MasterModuleConnection.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/DistantServer
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Thu Jul  9 21:25:46 2015 alexis mestag
// Last update Thu Aug 27 02:50:01 2015 alexis mestag
//

#include	<iostream>
#include	"Database/Database.hh"
#include	"Database/MasterModuleRepository.hh"
#include	"Network/Bridge.hh"
#include	"Network/MasterModuleConnection.hh"
#include	"Utils/JsonValidator.hh"

MasterModuleConnection::MasterModuleConnection(boost::asio::ip::tcp::socket socket,
					       ConnectionManager &connectionManager,
					       Bridge &bridge, Database &database) :
  JsonConnection(std::move(socket), connectionManager),
  _bridge(bridge), _database(database), _requestHandler(database) {
}

void		MasterModuleConnection::start() {
  this->recvUUID();
}

void		MasterModuleConnection::recvUUID() {
  this->recv([this](Json::Value const &json) {
      Json::Value	response;
      Json::UInt64	returnCode = 0;
      JsonValidator	connectCommand = {
	{"cmd", [](Json::Value const &value) -> bool { return (value.isString() && value.asString() == "connect"); }},
	{"id", &JsonValidator::isNonEmptyString}
      };

      if (connectCommand(json)) {
	std::unique_ptr<Database::transaction_type>	t(_database.getTransaction());
	std::string					uuid = json["id"].asString();

	try {
	  MasterModuleRepository			mmr(_database);
	  Repository<MasterModule>::pointer_type	module = mmr.getByUUID(uuid);

	  if (!module) {
	    module = std::make_shared<MasterModule>(uuid);
	    mmr.persist(*module);
	  }
	  _module = module;
	} catch (odb::exception const &e) {
	  t->rollback();
	  std::cerr << "Error: ODB exception occurred while retrieving/persisting module " << uuid << std::endl;
	  returnCode = 2;
	}
      } else {
	std::cerr << "Error: expected a connect command, got " << json.toStyledString() << std::endl;
	returnCode = 1;
      }

      response["returnCode"] = returnCode;
      this->send(response, [this, returnCode](boost::system::error_code const &ec, std::size_t) {
	  if (!ec && returnCode == 0) {
	    // MasterModuleConnection is now ready to be used by the Bridge
	    _bridge.registerModule(std::dynamic_pointer_cast<MasterModuleConnection>(this->shared_from_this()));
	  } else {
	    // Stop connection
	  }
	});
    });
}

void		MasterModuleConnection::handle(Json::Value const &json) {
  Json::Value	response;

  std::cout << "Received: " << json.toStyledString();
  _requestHandler(json, response);
  this->send(response, [this](boost::system::error_code const &ec, std::size_t) {
      if (!ec) {
	this->start();
      }
    });
}
