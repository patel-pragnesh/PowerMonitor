//
// UnitTest.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Apr 15 16:19:52 2015 alexis mestag
// Last update Sat Apr 18 19:47:40 2015 alexis mestag
//

#include		"UnitTest.hh"

UnitTest::UnitTest(std::string &&desc, UnitTestsClient &client, bool const manageSession) :
  _desc(std::move(desc)), _client(client), _manageSession(manageSession) {
}

bool			UnitTest::login() {
  Json::Value		request, response;

  request["cmd"] = "login";
  request["email"] = "alexis.mestag@epitech.eu";
  request["password"] = "alexis";

  this->send(request);
  this->recv(response);

  return (this->checkReturnCode(response, RequestHandler::eReturnCode::Ok));
}

void			UnitTest::send(Json::Value &request) {
  if (_manageSession && !_session.isNull()) {
    request["session"] = _session;
  }
  _client.send(request);
}

void			UnitTest::recv(Json::Value &response) {
  _client.recv(response);
  if (_manageSession) {
    _session = response["session"];
  }
}

bool			UnitTest::checkReturnCode(Json::Value const &response,
						  RequestHandler::eReturnCode const &retCode) {
  Json::Value const	&returnCodeValue = response["returnCode"];

  return (returnCodeValue.isUInt64() && returnCodeValue.asUInt64() == retCode);
}

std::string const	&UnitTest::getDescription() const {
  return (_desc);
}

Logger			&UnitTest::log() {
  return (_client.log());
}
