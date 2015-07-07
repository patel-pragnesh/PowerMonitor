//
// ModuleTest.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Jul  7 22:13:13 2015 alexis mestag
// Last update Tue Jul  7 22:42:45 2015 alexis mestag
//

#include	<chrono>
#include	<iostream>
#include	<ratio>
#include	<string>
#include	<vector>
#include	"Tests/ModuleTest.hh"

ModuleTest::ModuleTest(UnitTestsClient &client) :
  UnitTest("modules", client) {
}

bool		ModuleTest::operator()() {
  std::vector<std::pair<std::string, bool (ModuleTest::*)()>>	tests = {
    {"  - login: ", &ModuleTest::login},
    {"  - conso: ", &ModuleTest::getModuleConso},
  };
  bool		tmp, ret = true;

  for (auto it = tests.begin(); it != tests.end(); ++it) {
    std::cout << it->first;
    tmp = (this->*it->second)();
    std::cout << tmp << std::endl;
    ret &= tmp;
  }
  return (ret);
}

bool		ModuleTest::getModuleConso() {
  bool		ret = true;
  Json::Value	request, response;

  request["cmd"] = "getModuleConso";
  request["moduleId"] = static_cast<Json::Value::UInt64>(3);
  request["unitId"] = static_cast<Json::Value::UInt64>(2);

  using day_type	= std::chrono::duration<int, std::ratio<24 * 60 * 60>>;
  auto	now		= std::chrono::system_clock::now();
  auto	end		= now + day_type(30);
  request["beg"] = static_cast<Json::Value::UInt64>(now.time_since_epoch().count() * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den);
  request["end"] = static_cast<Json::Value::UInt64>(end.time_since_epoch().count() * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den);

  this->send(request);
  this->recv(response);
  
  return (ret);
}
