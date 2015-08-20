//
// SlaveModule.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Nov 29 01:03:21 2014 alexis mestag
// Last update Wed Apr  8 17:49:06 2015 alexis mestag
//

#include		"Entities/SlaveModule.hh"

SlaveModule::SlaveModule(std::string const &name,
			 std::string const &serialNumber) :
  Entity(),
  _name(name), _serialNumber(serialNumber) {
}

std::string const	&SlaveModule::getName() const {
  return (_name);
}

void			SlaveModule::setName(std::string const &name) {
  _name = name;
}

std::string const	&SlaveModule::getSerialNumber() const {
  return (_serialNumber);
}

void			SlaveModule::setSerialNumber(std::string const &serialNumber) {
  _serialNumber = serialNumber;
}

bool			SlaveModule::getStatus() const {
  return (_status);
}

void			SlaveModule::setStatus(bool const status) {
  _status = status;
}

SlaveModule::DefaultProfilePointer	SlaveModule::getDefaultProfile() const {
  return (_defaultProfile);
}

void			SlaveModule::setDefaultProfile(DefaultProfilePointer const &defaultProfile) {
  _defaultProfile = defaultProfile;
}

SlaveModule::InternalProfilePointer	SlaveModule::getInternalProfile() const {
  return (_internalProfile);
}

void				SlaveModule::serialize(Json::Value &json) const {
  Entity::serialize(json);
  json["name"] = _name;
  json["serialNumber"] = _serialNumber;
  json["status"] = _status;
  json["defaultProfileId"] = _defaultProfile ? static_cast<Json::UInt64>(_defaultProfile->getId()) : Json::Value();
  json["internalProfileId"] = static_cast<Json::UInt64>(_internalProfile->getId());
}
