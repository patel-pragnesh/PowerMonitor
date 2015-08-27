//
// LoginTest.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule/Unit tests/c++
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Apr 15 17:13:06 2015 alexis mestag
// Last update Thu Aug 27 03:24:03 2015 alexis mestag
//

#include		<vector>
#include		"Tests/LoginTest.hh"
#include		"Utils/JsonValidator.hh"

LoginTest::LoginTest(UnitTestsClient &client) :
  UnitTest("login", client, false) {
}

bool			LoginTest::operator()() {
  std::vector<std::pair<std::string, bool (LoginTest::*)()>> tests = {
    {"  - Bad user: ", &LoginTest::badUser},
    {"  - Bad password: ", &LoginTest::badPassword},
    {"  - Login ok: ", &LoginTest::loginOk}
  };
    bool	tmp, ret = true;
  for (auto it = tests.begin(); it != tests.end(); ++it) {
    std::cout << it->first;
    tmp = (this->*it->second)();
    std::cout << tmp << std::endl;
    ret &= tmp;
  }
  return (ret);
}

bool			LoginTest::badUser() {
  bool			ret = false;
  Json::Value		request, response;

  request["cmd"] = "login";
  request["email"] = "jean.petit@gmail.com";
  request["password"] = "jedanse";

  this->send(request);
  this->recv(response);

  ret = this->checkReturnCode(response, RequestHandler::eReturnCode::User_NotFound);
  return (ret);
}

bool			LoginTest::badPassword() {
  bool			ret = false;
  Json::Value		request, response;

  request["cmd"] = "login";
  request["email"] = "alexis.mestag@epitech.eu";
  request["password"] = "wrongPassword";

  this->send(request);
  this->recv(response);

  ret = this->checkReturnCode(response, RequestHandler::eReturnCode::Authentication_IncorrectPassword);
  return (ret);
}

bool			LoginTest::loginOk() {
  bool			ret = false;
  Json::Value		request, response;

  request["cmd"] = "login";
  request["email"] = "alexis.mestag@epitech.eu";
  request["password"] = "alexis";

  this->send(request);
  this->recv(response);

  JsonValidator		checker = {
    {"session", {
	{"userId", &Json::Value::isUInt64},
	{"token", &JsonValidator::isNonEmptyString}
      }
    },
    {"returnCode", &Json::Value::isUInt64}
  };

  ret = checker(response) && response["returnCode"].asUInt64() == RequestHandler::eReturnCode::Ok;
  return (ret);
}
