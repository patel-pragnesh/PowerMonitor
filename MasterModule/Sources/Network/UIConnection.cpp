//
// UIConnection.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Aug 25 01:45:47 2015 alexis mestag
// Last update Tue Aug 25 02:18:49 2015 alexis mestag
//

#include	"Network/UIConnection.hh"

UIConnection::UIConnection(boost::asio::ip::tcp::socket socket,
			   ConnectionManager &connectionManager,
			   Database &db) :
  JsonConnection(std::move(socket), connectionManager),
  _logger(), _requestHandler(db, _logger) {
}

void		UIConnection::start() {
  this->recv([this](Json::Value const &request) {
      _logger.out() << "Request: " << request.toStyledString() << std::endl;

      Json::Value	response;

      _requestHandler.handle(request, response);
      this->send(response, [this, response](boost::system::error_code const &error, std::size_t bytes_transferred) {
	  if (!error) {
	    _logger.out() << "Response: " << response.toStyledString() << std::endl;

	    this->start();
	  }
	});
    });
}
