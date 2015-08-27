//
// TimeSlotTest.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule/Unit tests
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Apr 29 22:09:21 2015 alexis mestag
// Last update Thu Aug 27 03:22:49 2015 alexis mestag
//

#include			"Tests/TimeSlotTest.hh"
#include			"Utils/JsonValidator.hh"

TimeSlotTest::TimeSlotTest(UnitTestsClient &client) :
  UnitTest("timeSlots", client) {
}

bool				TimeSlotTest::operator()() {
  std::vector<std::pair<std::string, bool (TimeSlotTest::*)()>> tests = {
    {"  - Login: ", &TimeSlotTest::login},
    {"  - Get random profile: ", &TimeSlotTest::getProfiles},
    {"  - Adding timeSlot: ", &TimeSlotTest::addTimeSlot},
    {"  - Added timeSlot is retrievable: ", &TimeSlotTest::regettingTimeSlots},
    {"  - With wrong profile: ", &TimeSlotTest::addTimeSlotProfileNotFound},
    {"  - Updating timeSlot: ", &TimeSlotTest::updateTimeSlot},
    {"  - With wrong id: ", &TimeSlotTest::updateTimeSlotNotFound},
    {"  - Deleting timeSlot: ", &TimeSlotTest::deleteTimeSlot},
    {"  - Deleted timeSlot is unretrievable: ", &TimeSlotTest::checkIfTimeSlotDeleted},
    {"  - With wrong id: ", &TimeSlotTest::deleteTimeSlotNotFound},
  };
  bool				tmp, ret = true;

  for (auto it = tests.begin(); it != tests.end(); ++it) {
    std::cout << it->first;
    tmp = (this->*it->second)();
    std::cout << tmp << std::endl;
    ret &= tmp;
  }
  return (ret);
}

bool				TimeSlotTest::getProfiles() {
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
    _timeSlots = _profile["timeSlots"];
  }
  return (ret);
}

bool				TimeSlotTest::addTimeSlot() {
  bool				ret;
  Json::Value			request, response;

  request["cmd"] = "addTimeSlot";
  request["profileId"] = _profile["id"];
  request["beg"]["day"] = 0; // Monday
  request["beg"]["minute"] = 3600; // 01:00
  request["end"]["day"] = 1; // Tuesday
  request["end"]["minute"] = 7200; // 02:00

  this->send(request);
  this->recv(response);

  JsonValidator			checker = {
    {"id", &Json::Value::isUInt64},
  };

  _addedTimeSlotId = response["id"];

  ret = checker(response) && this->checkReturnCode(response, RequestHandler::eReturnCode::Ok);
  return (ret);
}

bool				TimeSlotTest::regettingTimeSlots() {
  bool				ret = false;
  Json::Value			request, response;

  request["cmd"] = "getProfile";
  request["id"] = _profile["id"];

  this->send(request);
  this->recv(response);

  Json::Value const		&timeSlots = response["profile"]["timeSlots"];
  Json::Value const		*p;

  for (unsigned int i = 0; i < timeSlots.size(); ++i) {
    p = &timeSlots[i];

    if ((*p)["id"] == _addedTimeSlotId) {
      ret = true;
      break;
    }
  }  
  return (ret);
}

bool				TimeSlotTest::addTimeSlotProfileNotFound() {
  bool				ret;
  Json::Value			request, response;

  request["cmd"] = "addTimeSlot";
  request["profileId"] = std::numeric_limits<Json::Value::UInt64>::max();
  request["beg"]["day"] = 0; // Monday
  request["beg"]["minute"] = 3600; // 01:00
  request["end"]["day"] = 1; // Tuesday
  request["end"]["minute"] = 7200; // 02:00

  this->send(request);
  this->recv(response);
    
  ret = this->checkReturnCode(response, RequestHandler::eReturnCode::Profile_NotFound);
  return (ret);
}

bool				TimeSlotTest::updateTimeSlot() {
  bool				ret;
  Json::Value			request, response;

  request["cmd"] = "updateTimeSlot";
  request["id"] = _addedTimeSlotId;
  request["beg"]["day"] = 6;
  request["beg"]["minute"] = 3650;
  request["end"]["day"] = 4;
  request["end"]["minute"] = 7300;

  this->send(request);
  this->recv(response);

  ret = this->checkReturnCode(response, RequestHandler::eReturnCode::Ok);
  return (ret);
}

bool				TimeSlotTest::updateTimeSlotNotFound() {
  bool				ret;
  Json::Value			request, response;

  request["cmd"] = "updateTimeSlot";
  request["id"] = std::numeric_limits<Json::Value::UInt64>::max();
  request["beg"]["day"] = 4;
  request["beg"]["minute"] = 3650;
  request["end"]["day"] = 4;
  request["end"]["minute"] = 7300;

  this->send(request);
  this->recv(response);

  ret = this->checkReturnCode(response, RequestHandler::eReturnCode::TimeSlot_NotFound);
  return (ret);
}

bool				TimeSlotTest::deleteTimeSlot() {
  bool				ret;
  Json::Value			request, response;

  request["cmd"] = "deleteTimeSlot";
  request["id"] = _addedTimeSlotId;

  this->send(request);
  this->recv(response);

  ret = this->checkReturnCode(response, RequestHandler::eReturnCode::Ok);
  return (ret);
}

bool				TimeSlotTest::checkIfTimeSlotDeleted() {
  bool				ret = false;
  Json::Value			request, response;

  request["cmd"] = "getProfile";
  request["id"] = _profile["id"];

  this->send(request);
  this->recv(response);

  ret = false;
  unsigned int			i;
  for (i = 0; i < response["profile"]["timeSlots"].size(); ++i) {
    if (response["profile"]["timeSlots"][i]["id"] == _addedTimeSlotId) {
      break;
    }
  }
  ret = i == response["profile"]["timeSlots"].size();
  return (ret);
}

bool				TimeSlotTest::deleteTimeSlotNotFound() {
  bool				ret = false;
  Json::Value			request, response;

  request["cmd"] = "deleteTimeSlot";
  request["id"] = _addedTimeSlotId;

  this->send(request);
  this->recv(response);

  ret = this->checkReturnCode(response, RequestHandler::eReturnCode::TimeSlot_NotFound);
  return (ret);
}
