//
// AlertTest.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Apr 18 19:09:53 2015 alexis mestag
// Last update Wed Apr 29 23:01:37 2015 alexis mestag
//

#include			<chrono>
#include			<limits>
#include			<random>

#include			"Tests/AlertTest.hh"
#include			"Utils/JsonValidator.hh"

AlertTest::AlertTest(UnitTestsClient &client) :
  UnitTest("alerts", client) {
}

bool				AlertTest::operator()() {
  bool				login = this->login();
  bool				gps = false;
  bool				aa, recheck, aanp, aanu;
  bool				ua, uaanf, uaunf;
  bool				da, cda, danf;

  if (login) {
    gps = this->getProfiles();
    if (gps) {
      this->log().out() << "Adding alert: " << (aa = this->addAlert()) << std::endl;
      this->log().out() << "Is the new alert retrievable ? " << (recheck = this->regettingAlerts()) << std::endl;
      this->log().out() << "With wrong profile: " << (aanp = this->addAlertNoSuchProfile()) << std::endl;
      this->log().out() << "With wrong unit: " << (aanu = this->addAlertNoSuchUnit()) << std::endl;

      this->log().out() << "Updating alert: " << (ua = this->updateAlert()) << std::endl;
      this->log().out() << "With wrong alert id: " << (uaanf = this->updateAlertNotFound()) << std::endl;
      this->log().out() << "With wrong unit: " << (uaunf = this->updateAlertUnitNotFound()) << std::endl;

      this->log().out() << "Deleteting alert: " << (da = this->deleteAlert()) << std::endl;
      this->log().out() << "Is the delete alert unretrievable ? " << (cda = this->checkIfAlertDeleted()) << std::endl;
      this->log().out() << "With wrong alert: " << (danf = this->deleteAlertNotFound()) << std::endl;
    }
  }
  return (login && gps && aa && recheck && aanp && aanu
	  && ua && uaanf && uaunf
	  && da && cda && danf);
}

bool				AlertTest::getProfiles() {
  bool				ret = false;
  Json::Value			request, response;

  request["cmd"] = "getProfiles";

  this->send(request);
  this->recv(response);

  _profiles = response["profiles"];
  ret = _profiles.isArray();
  if (ret) {
    unsigned long			arraySize = _profiles.size();
    unsigned int			seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine		generator(seed);
    std::uniform_int_distribution<int>	distribution(0, arraySize - 1);

    _profile = _profiles[distribution(generator)];

    request["cmd"] = "getProfile";
    request["id"] = _profile["id"];

    this->send(request);
    this->recv(response);

    _profile = response["profile"];
    _alerts = _profile["alerts"];
  }
  return (ret);
}

bool				AlertTest::addAlert() {
  bool				ret = false;
  Json::Value			request, response;

  request["cmd"] = "addAlert";
  request["profileId"] = _profile["id"];
  request["unitId"] = 1;
  request["value"] = 3000;

  this->send(request);
  this->recv(response);

  JsonValidator			checker = {
    {"id", &Json::Value::isUInt64},
  };

  _addedAlertId = response["id"];
  
  ret = checker(response) && this->checkReturnCode(response, RequestHandler::eReturnCode::Ok);
  return (ret);
}

bool				AlertTest::regettingAlerts() {
  bool				ret = false;
  Json::Value			request, response;

  request["cmd"] = "getProfile";
  request["id"] = _profile["id"];

  this->send(request);
  this->recv(response);

  Json::Value const		&alerts = response["profile"]["alerts"];
  Json::Value const		*p;

  for (unsigned int i = 0; i < alerts.size(); ++i) {
    p = &alerts[i];

    if ((*p)["id"] == _addedAlertId) {
      ret = true;
      break;
    }
  }
  
  return (ret);
}

bool				AlertTest::addAlertNoSuchProfile() {
  bool				ret = false;
  Json::Value			request, response;

  request["cmd"] = "addAlert";
  request["profileId"] = std::numeric_limits<Json::Value::UInt64>::max();
  request["unitId"] = 1;
  request["value"] = 3000;

  this->send(request);
  this->recv(response);

  ret = this->checkReturnCode(response, RequestHandler::eReturnCode::Profile_NotFound);
  return (ret);
}

bool				AlertTest::addAlertNoSuchUnit() {
  bool				ret = false;
  Json::Value			request, response;

  request["cmd"] = "addAlert";
  request["profileId"] = _profile["id"];
  request["unitId"] = std::numeric_limits<Json::Value::UInt64>::max();
  request["value"] = 3000;

  this->send(request);
  this->recv(response);

  ret = this->checkReturnCode(response, RequestHandler::eReturnCode::Unit_NotFound);
  return (ret);
}

bool				AlertTest::updateAlert() {
  bool				ret = false;
  Json::Value			request, response;

  request["cmd"] = "updateAlert";
  request["id"] = _addedAlertId;
  request["unitId"] = 1;
  request["value"] = 6000;

  this->send(request);
  this->recv(response);

  ret = this->checkReturnCode(response, RequestHandler::eReturnCode::Ok);
  return (ret);
}

bool				AlertTest::updateAlertNotFound() {
  bool				ret = false;
  Json::Value			request, response;

  request["cmd"] = "updateAlert";
  request["id"] = std::numeric_limits<Json::Value::UInt64>::max();
  request["unitId"] = 1;
  request["value"] = 3000;

  this->send(request);
  this->recv(response);

  ret = this->checkReturnCode(response, RequestHandler::eReturnCode::Alert_NotFound);
  return (ret);
}

bool				AlertTest::updateAlertUnitNotFound() {
  bool				ret = false;
  Json::Value			request, response;

  request["cmd"] = "updateAlert";
  request["id"] = _addedAlertId;
  request["unitId"] = std::numeric_limits<Json::Value::UInt64>::max();
  request["value"] = 3000;

  this->send(request);
  this->recv(response);

  ret = this->checkReturnCode(response, RequestHandler::eReturnCode::Unit_NotFound);
  return (ret);
}

bool				AlertTest::deleteAlert() {
  bool				ret = false;
  Json::Value			request, response;

  request["cmd"] = "deleteAlert";
  request["id"] = _addedAlertId;

  this->send(request);
  this->recv(response);

  ret = this->checkReturnCode(response, RequestHandler::eReturnCode::Ok);
  return (ret);
}

bool				AlertTest::checkIfAlertDeleted() {
  bool				ret = false;
  Json::Value			request, response;

  request["cmd"] = "getProfile";
  request["id"] = _profile["id"];

  this->send(request);
  this->recv(response);

  ret = false;
  unsigned int			i;
  for (i = 0; i < response["profile"]["alerts"].size(); ++i) {
    if (response["profile"]["alerts"][i]["id"] == _addedAlertId) {
      break;
    }
  }
  ret = i == response["profile"]["alerts"].size();
  return (ret);
}

bool				AlertTest::deleteAlertNotFound() {
  bool				ret = false;
  Json::Value			request, response;

  request["cmd"] = "deleteAlert";
  request["id"] = _addedAlertId;

  this->send(request);
  this->recv(response);

  ret = this->checkReturnCode(response, RequestHandler::eReturnCode::Alert_NotFound);
  return (ret);
}
