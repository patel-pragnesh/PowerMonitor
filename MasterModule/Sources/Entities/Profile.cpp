//
// Profile.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sat Nov 29 01:41:17 2014 alexis mestag
// Last update Tue Apr 14 15:06:34 2015 alexis mestag
//

#include		<algorithm>
#include		"Entities/Profile.hh"

Profile::Profile(int const polling) :
  Entity(),
  _polling(polling) {
}

int			Profile::getPolling() const {
  return (_polling);
}

void			Profile::setPolling(int const polling) {
  _polling = polling;
}

Profile::Alerts const	&Profile::getAlerts() const {
  return (_alerts);
}

void			Profile::setAlerts(Alerts const &alerts) {
  _alerts = alerts;
}

void			Profile::addAlert(Alerts::value_type const &alert) {
  _alerts.push_back(alert);
}

void			Profile::removeAlert(Alerts::value_type const &alert) {
  _alerts.remove_if([&](Alerts::value_type const &a) {
      return (*a.lock() == *alert.lock());
    });
}

Profile::TimeSlots const	&Profile::getTimeSlots() const {
  return (_timeSlots);
}

void				Profile::setTimeSlots(TimeSlots const &timeSlots) {
  _timeSlots = timeSlots;
}

void				Profile::addTimeSlot(TimeSlots::value_type const &timeSlot) {
  _timeSlots.push_back(timeSlot);
}

void				Profile::removeTimeSlot(TimeSlots::value_type const &timeSlot) {
  _timeSlots.remove_if([&](TimeSlots::value_type const &t) {
      return (*t.lock() == *timeSlot.lock());
    });
}

void				Profile::serialize(Json::Value &json) const {
  Entity::serialize(json);
  json["polling"] = _polling;

  // // Handle Alerts ...
  // Json::Value			alerts(Json::ValueType::arrayValue);
  // std::for_each(_alerts.begin(), _alerts.end(), [&](Alerts::value_type alert) {
  //     Json::Value		alertValue(Json::ValueType::objectValue);

  //     (alert.lock())->serialize(alertValue);
  //     alerts.append(alertValue);
  //   });
  // json["alerts"] = alerts;

  // // Handle TimeSlots ...
  // Json::Value			timeSlots(Json::ValueType::arrayValue);
  // std::for_each(_timeSlots.begin(), _timeSlots.end(), [&](TimeSlots::value_type const &timeSlot) {
  //     Json::Value		timeSlotValue(Json::ValueType::objectValue);

  //     (timeSlot.lock())->serialize(timeSlotValue);
  //     timeSlots.append(timeSlotValue);
  //   });
  // json["timeSlots"] = timeSlots;
}
