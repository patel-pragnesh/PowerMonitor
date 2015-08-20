//
// RequestHandler.cpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb  9 02:45:23 2015 alexis mestag
// Last update Sun Jun 21 00:13:36 2015 alexis mestag
//

#include		<array>
#include		<iostream>
#include		<memory>

#include		<cryptopp/sha.h>
#include		<cryptopp/hex.h>

#include		"Database/Repository.hpp"
#include		"Database/AlertRepository.hh"
#include		"Database/DefaultProfileRepository.hh"
#include		"Database/ReadingRepository.hh"
#include		"Database/SessionRepository.hh"
#include		"Database/TimeSlotRepository.hh"
#include		"Database/UserRepository.hh"

#include		"Entities/Information.hh"
#include		"Entities/InternalProfile-odb.hxx"
#include		"Entities/Profile-odb.hxx"
#include		"Entities/SlaveModule-odb.hxx"
#include		"Entities/Unit-odb.hxx"
#include		"Entities/Views/SlaveModuleCount-odb.hxx"

#include		"Network/RequestHandler.hh"
#include		"Utils/Bytes.hpp"
#include		"Utils/JsonValidator.hh"

typedef std::pair<bool (RequestHandler::*)(Json::Value const &, Json::Value &), JsonValidator>	handler_validator;
typedef std::map<std::string, handler_validator>						map_to_handler_validator;

RequestHandler::RequestHandler(Database &database, Logger &logger) :
  _database(database), _logger(logger) {
}

void			RequestHandler::persistSession() {
  if (_session) {
    SessionRepository		sr(_database);
    Database::transaction_type	*t(_database.getTransaction());

    // Should update if already persistent
    sr.persist(*_session);

    t->commit();
    _logger.out() << "Session persisted" << std::endl;
  }
}

bool			RequestHandler::handle(Json::Value const &request, Json::Value &response) {
  static JsonValidator	requestValidator = {{"cmd", &JsonValidator::isNonEmptyString}};
  bool			ret = false;

  response.clear();
  if (requestValidator(request)) {
    ret = this->cmdHandler(request, response);
  } else {
    _logger.err() << "Request doesn't contain a 'cmd' field" << std::endl;
    this->returnCode(response, Generic_NotWellFormattedRequest);
  }
  if (ret) {
    this->returnCode(response, Ok);
  }
  return (ret);
}

bool			RequestHandler::cmdHandler(Json::Value const &request, Json::Value &response) {
  static map_to_handler_validator	authenticatedRouter = {
    {"changePassword", {
	&RequestHandler::changePassword, {{"password", &JsonValidator::isNonEmptyString}}
      }
    }, {"getModule", {
	&RequestHandler::getModule, {{"id", &Json::Value::isUInt64}}
      }
    }, {"getModules", {
	&RequestHandler::getModules, {}
      }
    }, {"turnOnOff", {
	&RequestHandler::turnOnOff, {{"id", &Json::Value::isUInt64},
				     {"status", &Json::Value::isBool}}
      }
    }, {"renameModule", {
	&RequestHandler::renameModule, {{"id", &Json::Value::isUInt64},
					{"name", &JsonValidator::isNonEmptyString}}
      }
    }, {"updateModuleDefaultProfile", {
	&RequestHandler::updateModuleDefaultProfile, {{"id", &Json::Value::isUInt64},
						      {"defaultProfileId", [](Json::Value const &v) -> bool {
							  return (v.isUInt64() || v.isNull());
							}
						      }}
      }
    }, {"getModuleConso", {
	&RequestHandler::getModuleConso, {
	  {"moduleId", &Json::Value::isUInt64},
	  {"unitId", &Json::Value::isUInt64},
	  {"beg", &Json::Value::isUInt64},
	  {"end", &Json::Value::isUInt64}
	}
      }
    }, {"getProfile", {
	&RequestHandler::getProfile, {{"id", &Json::Value::isUInt64}}
      }
    }, {"getProfiles", {
	&RequestHandler::getProfiles, {}
      }
    }, {"addProfile", {
	&RequestHandler::addProfile, {{"name", &JsonValidator::isNonEmptyString}}
      }
    }, {"deleteProfile", {
	&RequestHandler::deleteProfile, {{"id", &Json::Value::isUInt64}}
      }
    }, {"updateProfilePolling", {
	&RequestHandler::updateProfilePolling, {{"id", &Json::Value::isUInt64},
						{"polling", &Json::Value::isInt}}
      }
    }, {"addAlert", {
	&RequestHandler::addAlert, {{"profileId", &Json::Value::isUInt64},
				    {"unitId", &Json::Value::isUInt64},
				    {"value", &Json::Value::isDouble}}
      }
    }, {"updateAlert", {
	&RequestHandler::updateAlert, {{"id", &Json::Value::isUInt64},
				       {"unitId", &Json::Value::isUInt64},
				       {"value", &Json::Value::isDouble}}
      }
    }, {"deleteAlert", {
	&RequestHandler::deleteAlert, {{"id", &Json::Value::isUInt64}}
      }
    }, {"addAlertUser", {
	&RequestHandler::addAlertUser, {{"alertId", &Json::Value::isUInt64},
					{"userId", &Json::Value::isUInt64}}
      }
    }, {"deleteAlertUser", {
	&RequestHandler::deleteAlertUser, {{"alertId", &Json::Value::isUInt64},
					   {"userId", &Json::Value::isUInt64}}
      }
    }, {"addTimeSlot", {
	&RequestHandler::addTimeSlot, {{"profileId", &Json::Value::isUInt64},
				       {"beg", {
					   {"day", &Json::Value::isUInt},
					   {"minute", &Json::Value::isUInt}
					 }},
				       {"end", {
					   {"day", &Json::Value::isUInt},
					   {"minute", &Json::Value::isUInt}					   
					 }}}
      }
    }, {"updateTimeSlot", {
	&RequestHandler::updateTimeSlot, {{"id", &Json::Value::isUInt64},
					  {"beg", {
					      {"day", &Json::Value::isUInt},
					      {"minute", &Json::Value::isUInt}
					    }},
					  {"end", {
					      {"day", &Json::Value::isUInt},
					      {"minute", &Json::Value::isUInt}					   
					    }}}
      }
    }, {"deleteTimeSlot", {
	&RequestHandler::deleteTimeSlot, {{"id", &Json::Value::isUInt64}}
      }
    }
  };
  static map_to_handler_validator	unauthenticatedRouter = {
    {"login", {
	&RequestHandler::login, {{"email", &JsonValidator::isNonEmptyString},
				 {"password", &JsonValidator::isNonEmptyString}}
      }
    }
  };
  bool					isAuthenticated;
  bool					ret = false;

  std::string					cmd = request["cmd"].asString();
  map_to_handler_validator::const_iterator	it = authenticatedRouter.find(cmd);

  if (it != authenticatedRouter.end()) {
    isAuthenticated = this->isAuthenticated(request, response);
    if (isAuthenticated) {
      // OK // Regenerate a session for the response
      _session->generateToken();
    } else {
      // Access denied
      _logger.err() << "Unauthenticated request sent an authentication-required command" << std::endl;
      this->returnCode(response, Generic_InvalidSession);
      return (false);
    }
  } else {
    it = unauthenticatedRouter.find(cmd);
  }

  if (it != authenticatedRouter.end() && it != unauthenticatedRouter.end()) {
    if (it->second.second(request)) {
      Database::transaction_type			*t(_database.getTransaction());

      try {
	ret = (this->*it->second.first)(request, response);
	t->commit();
      } catch (odb::exception const &e) {
	_logger.err() << "ODB Exception: " << e.what() << std::endl;
	ret = false;
	t->rollback();
      }
      delete t;
    } else {
      _logger.err() << "Not well formatted request (fields are missing)" << std::endl;
      this->returnCode(response, Generic_NotWellFormattedRequest);
    }
  } else {
    _logger.err() << "Command not found '" << cmd << "'" << std::endl;
    this->returnCode(response, Generic_CommandNotFound);
  }

  if (_session) {
    _session->serialize(response["session"]);
  }
  return (ret);
}

bool			RequestHandler::isAuthenticated(Json::Value const &request,
							Json::Value &response) {
  static JsonValidator	sessionValidator = {
    {"session", {
	{"token", &JsonValidator::isNonEmptyString},
	{"userId", &Json::Value::isUInt64}
      }
    }
  };
  bool			ret = false;

  if (sessionValidator(request)) { // The session JSON object is well formatted
    Session::token_type	token;

    Bytes::hexDecode(request["session"]["token"].asString(), token);
    if (!_session) { // The session is not initialized
      Database::transaction_type	*t(_database.getTransaction());
      SessionRepository			sr(_database);
      Repository<Session>::pointer_type	session = sr.getByToken(token);

      if (session) { // Maybe there's not any previously persisted session
	_session = session;
	//sr.erase(_session);
      }
      t->commit();
    }

    if (_session) { // If there is, then compare the 2 tokens. If not, then the request is not authenticated
      ret = token == _session->getToken();

      if (ret) { // This is processed too many times but osef
	_logger.setHeader(_session->getUser()->getName());
      }
    }
  } else {
    _logger.err() << "Session object not well formatted: " << request["session"].toStyledString(); // std::endl already in StyledString
    this->returnCode(response, Generic_NotWellFormattedRequest);
  }
  return (ret);
}

bool			RequestHandler::login(Json::Value const &request,
					      Json::Value &response) {
  bool					ret = false;
  std::string				email = request["email"].asString();
  std::string				password = request["password"].asString();
  UserRepository			ur(_database);
  Repository<User>::pointer_type	user = ur.getByEmail(email);

  if (user) {
    CryptoPP::SHA256			sha256;
    User::hash_type			digest;

    sha256.Update((byte const *)password.data(), password.size());
    sha256.Update((byte const *)user->getSalt().data(), user->getSalt().size());
    sha256.Final(digest.data());

    // _logger.out() << password << " + " << Bytes::hexEncode(user->getSalt()) << std::endl;
    // _logger.out() << Bytes::hexEncode(digest) << " <==> " << Bytes::hexEncode(user->getHash()) << std::endl;
    ret = digest == user->getHash();
    if (ret) {
      // Generate a session
      _session.reset(new Session(user));
      _logger.setHeader(user->getName());
    } else {
      _logger.err() << "Incorrect password" << std::endl;
      this->returnCode(response, Authentication_IncorrectPassword);
    }
  } else {
    _logger.err() << "User not found: " << email << std::endl;
    this->returnCode(response, User_NotFound);
  }
  return (ret);
}

/**
 * Users
 */

bool			RequestHandler::changePassword(Json::Value const &request, Json::Value &response) {
  bool			ret = false;
  std::string		password = request["password"].asString();

  if (!password.empty()) {
    auto		user = _session->getUser();
    UserRepository	ur(_database);

    user->setPassword(password);
    ur.update(*user);
    ret = true;
  } else {
    this->returnCode(response, User_InvalidPassword);
  }
  return (ret);
}
 
/**
 * Modules
 */

bool			RequestHandler::getModule(Json::Value const &request, Json::Value &response) {
  return (this->getEntity<SlaveModule>("module", Module_NotFound, request, response));
}

bool			RequestHandler::getModules(Json::Value const &,
						   Json::Value &response) {
  Repository<SlaveModule>		r(_database);
  Repository<SlaveModule>::result_type	entities = r.getAll();
  Json::Value				array(Json::ValueType::arrayValue);

  std::for_each(entities.begin(), entities.end(), [&](SlaveModule const &entity) {
      Json::Value				value(Json::ValueType::objectValue);
      SlaveModule::DefaultProfilePointer	defaultProfile = entity.getDefaultProfile();
      Json::Value				&dpValue = value["defaultProfile"];

      entity.serialize(value);

      if (defaultProfile) {
	dpValue["id"] = value["defaultProfileId"];
	dpValue["name"] = defaultProfile->getName();
      }
      value.removeMember("defaultProfileId");
      
      array.append(value);
    });
  response["modules"] = array;
  return (true);
}

bool			RequestHandler::turnOnOff(Json::Value const &request, Json::Value &response) {
  Repository<SlaveModule>			r(_database);
  Repository<SlaveModule>::id_type		id = request["id"].asUInt64();
  Repository<SlaveModule>::pointer_type		entity = r.getById(id);
  bool						ret = false;

  if (entity) {
    bool					onOrOff = request["status"].asBool();

    if (entity->getStatus() != onOrOff) {
      ret = true; // Here should be called the function to actually turn on or off the module
      if (ret) { // If the operation succeeded, update the database.
	entity->setStatus(onOrOff);
	r.update(*entity);
      }
      else {
	this->returnCode(response, Module_CannotUpdateState);
      }
    }
    else {
      this->returnCode(response, Module_AlreadyInGivenState);
    }
  }
  else {
    this->returnCode(response, Module_NotFound);
  }
  
  return (ret);
}

bool			RequestHandler::renameModule(Json::Value const &request,
						     Json::Value &response) {
  Repository<SlaveModule>			r(_database);
  Repository<SlaveModule>::id_type		id = request["id"].asUInt64();
  Repository<SlaveModule>::pointer_type		entity = r.getById(id);
  bool						ret = false;

  if (entity) {
    // There should be check on an already existing name
    entity->setName(request["name"].asString());
    r.update(*entity);
    ret = true;
  }
  else {
    this->returnCode(response, Module_NotFound);
  }
  return (ret);
}

bool			RequestHandler::updateModuleDefaultProfile(Json::Value const &request,
								   Json::Value &response) {
  Repository<SlaveModule>			r(_database);
  Repository<SlaveModule>::id_type		id = request["id"].asUInt64();
  Repository<SlaveModule>::pointer_type		entity = r.getById(id);
  bool						ret = false;

  if (entity) {
    Json::Value	const				&dpId = request["defaultProfileId"];
    Repository<DefaultProfile>::pointer_type	defaultProfile;

    if (dpId.isNull()) {
      defaultProfile = nullptr;
      ret = true;
    }
    else {
      Repository<DefaultProfile>		rdp(_database);
      Repository<DefaultProfile>::id_type	defaultProfileId = dpId.asUInt64();

      defaultProfile = rdp.getById(defaultProfileId);
      ret = defaultProfile != nullptr;
    }
    if (ret) {
      entity->setDefaultProfile(defaultProfile);
      r.update(*entity);
    } else {
      this->returnCode(response, Profile_NotFound);
    } 
  }
  else {
    this->returnCode(response, Module_NotFound);
  }  
  return (ret);
}

bool			RequestHandler::getProfile(Json::Value const &request, Json::Value &response) {
  bool					ret = false;
  Repository<Profile>			pr(_database);
  Repository<Profile>::id_type		id = request["id"].asUInt64();
  Repository<Profile>::pointer_type	profile = pr.getById(id);

  if (profile) {
    Json::Value				&profileJson = response["profile"];
    profile->serialize(profileJson);

    // Add alerts
    Json::Value				alertsJson(Json::ValueType::arrayValue);
    AlertRepository			ar(_database);
    Repository<Alert>::result_type	alerts = ar.getByProfile(*profile);

    std::for_each(alerts.begin(), alerts.end(), [&](Alert const &alert) {
	Json::Value			alertJson(Json::ValueType::objectValue);

	alert.serialize(alertJson);
	alertsJson.append(alertJson);
      });
    profileJson["alerts"] = alertsJson;

    // Add timeSlots
    Json::Value				timeSlotsJson(Json::ValueType::arrayValue);
    TimeSlotRepository			tsr(_database);
    Repository<TimeSlot>::result_type	timeSlots = tsr.getByProfile(*profile);

    std::for_each(timeSlots.begin(), timeSlots.end(), [&](TimeSlot const &timeSlot) {
	Json::Value			timeSlotJson(Json::ValueType::objectValue);

	timeSlot.serialize(timeSlotJson);
	timeSlotsJson.append(timeSlotJson);
      });
    profileJson["timeSlots"] = timeSlotsJson;
    
    ret = true;
  }
  else {
    this->returnCode(response, Profile_NotFound);
  }
  return (ret);
}

bool			RequestHandler::getProfiles(Json::Value const &request, Json::Value &response) {
  return (this->getEntities<DefaultProfile>("profiles", request, response));
}

bool			RequestHandler::addProfile(Json::Value const &request, Json::Value &response) {
  DefaultProfileRepository			r(_database);
  std::string const				name = request["name"].asString();
  Repository<DefaultProfile>::pointer_type	entity = r.getByName(name);
  bool						ret = false;

  if (!entity) {
    int						polling = request["polling"].asInt();
    DefaultProfile				*dp = new DefaultProfile(name, polling);

    r.persist(*dp);
    response["profileId"] = static_cast<Json::UInt64>(dp->getId());
    ret = true;
  }
  else {
    _logger.err() << "Profile name already exists (" << name << ')' << std::endl;
    this->returnCode(response, Profile_NameAlreadyExists);
  }
  return (ret);   
}
 
bool			RequestHandler::deleteProfile(Json::Value const &request,
						      Json::Value &response) {
  Repository<DefaultProfile>			r(_database);
  Repository<DefaultProfile>::id_type		id = request["id"].asUInt64();
  Repository<DefaultProfile>::pointer_type	entity = r.getById(id);
  bool						ret = false;

  if (entity) {
    Repository<SlaveModuleCount>::query_type	q(Repository<SlaveModuleCount>::query_type::defaultProfile == id);

    // if (entity->getModules().empty()) {
    
    if (_database.query_value(q).count == 0) {
      r.erase(*entity);
      ret = true;
    } else {
      _logger.err() << "Profile is used by modules: cannot delete it" << std::endl;
      this->returnCode(response, Profile_StillInUse);
    }
  }
  else {
    _logger.err() << "No such profile id: " << id << std::endl;
    this->returnCode(response, Profile_NotFound);
  }
  return (ret);
}

bool			RequestHandler::updateProfilePolling(Json::Value const &request, Json::Value &response) {
  Repository<Profile>			r(_database);
  Repository<Profile>::id_type		id = request["id"].asUInt64();
  Repository<Profile>::pointer_type	entity = r.getById(id);
  bool					ret = false;

  if (entity) {
    int					polling = request["polling"].asInt();

    entity->setPolling(polling);
    r.update(*entity);
    ret = true;
  }
  else {
    _logger.err() << "No such profile id: " << id << std::endl;
    this->returnCode(response, Profile_NotFound);
  }  
  return (ret);
}

bool			RequestHandler::getModuleConso(Json::Value const &request, Json::Value &response) {
  bool					ret = false;
  Repository<SlaveModule>::id_type	moduleId = request["moduleId"].asUInt64();
  Repository<SlaveModule>		smr(_database);
  Repository<SlaveModule>::pointer_type	module = smr.getById(moduleId);
  
  if (module) {
    Repository<Unit>::id_type		unitId = request["unitId"].asUInt64();
    Repository<Unit>			ur(_database);
    Repository<Unit>::pointer_type	unit = ur.getById(unitId);

    if (unit) {
      ReadingRepository			rr(_database);
      auto				beg = Time::Point(request["beg"].asUInt64());
      auto				end = Time::Point(request["end"].asUInt64());
      auto				result = rr.getBetween(module, unit,
							       beg, end);

      Json::Value			&infos = (response["infos"] = Json::Value(Json::ValueType::arrayValue));
      for (auto const &r: result) {
	Json::Value			tmp;

	r.serialize(tmp);
	infos.append(tmp);
      }
      ret = true;
    } else {
      this->returnCode(response, Unit_NotFound);
    }
  } else {
    this->returnCode(response, Module_NotFound);
  }
  return (ret);
}


bool			RequestHandler::addAlert(Json::Value const &request, Json::Value &response) {
  bool			ret = false;
  Repository<Profile>::id_type		profileId = request["profileId"].asUInt64();
  Repository<Profile>			pr(_database);
  Repository<Profile>::pointer_type	profile = pr.getById(profileId);

  if (profile) {
    Repository<Unit>::id_type		unitId = request["unitId"].asUInt64();
    Repository<Unit>			ur(_database);
    Repository<Unit>::pointer_type	unit = ur.getById(unitId);

    if (unit) {
      double				value = request["value"].asDouble();
      Alert				alert(Information(unit, value), profile);
      Repository<Alert>			ar(_database);
      Repository<Alert>::id_type	alertId = ar.persist(alert);

      response["id"] = static_cast<Json::UInt64>(alertId);
      ret = true;
    }
    else {
      _logger.err() << "No such unit: " << unitId << std::endl;
      this->returnCode(response, Unit_NotFound);
    }
  }
  else {
    _logger.err() << "No such profile: " << profileId << std::endl;
    this->returnCode(response, Profile_NotFound);
  }
  return (ret);
}

bool			RequestHandler::updateAlert(Json::Value const &request, Json::Value &response) {
  bool			ret = false;
  Repository<Alert>::id_type		id = request["id"].asUInt64();
  Repository<Alert>			ar(_database);
  Repository<Alert>::pointer_type	alert = ar.getById(id);

  if (alert) {
    Repository<Unit>::id_type		unitId = request["unitId"].asUInt64();
    Repository<Unit>			ur(_database);
    Repository<Unit>::pointer_type	unit = ur.getById(unitId);

    if (unit) {
      double				value = request["value"].asDouble();

      alert->setUnit(unit);
      alert->setValue(value);
      ar.update(*alert);
      ret = true;
    }
    else {
      _logger.err() << "No such unit: " << unitId << std::endl;
      this->returnCode(response, Unit_NotFound);
    }
  }
  else {
    _logger.err() << "No such alert: " << id << std::endl;
    this->returnCode(response, Alert_NotFound);
  }
  return (ret);
}

bool			RequestHandler::deleteAlert(Json::Value const &request, Json::Value &response) {
  bool			ret = false;
  Repository<Alert>			ar(_database);
  Repository<Alert>::id_type		id = request["id"].asUInt64();
  Repository<Alert>::pointer_type	alert = ar.getById(id);

  if (alert) {
    ar.erase(*alert);
    ret = true;
  }
  else {
    _logger.err() << "No such alert: " << id << std::endl;
    this->returnCode(response, Alert_NotFound);
  }
  return (ret);
}

bool			RequestHandler::addAlertUser(Json::Value const &request, Json::Value &response) {
  bool			ret = false;
  Repository<Alert>			ar(_database);
  Repository<Alert>::id_type		alertId = request["alertId"].asUInt64();
  Repository<Alert>::pointer_type	alert = ar.getById(alertId);

  if (alert) {
    Repository<User>			ur(_database);
    Repository<User>::id_type		userId = request["userId"].asUInt64();
    Repository<User>::pointer_type	user = ur.getById(userId);

    if (user) { // There should be a check to know if the user is already added
      alert->addUser(user);
      ar.update(*alert);
      ret = true;
    }
    else {
      _logger.err() << "No such user: " << userId << std::endl;
      this->returnCode(response, User_NotFound);
    }
  }
  else {
    _logger.err() << "No such alert: " << alertId << std::endl;
    this->returnCode(response, Alert_NotFound);
  }
  return (ret);
}

bool			RequestHandler::deleteAlertUser(Json::Value const &request, Json::Value &response) {
  bool			ret = false;
  Repository<Alert>			ar(_database);
  Repository<Alert>::id_type		alertId = request["alertId"].asUInt64();
  Repository<Alert>::pointer_type	alert = ar.getById(alertId);

  if (alert) {
    Repository<User>			ur(_database);
    Repository<User>::id_type		userId = request["userId"].asUInt64();
    Repository<User>::pointer_type	user = ur.getById(userId);

    if (user) {
      alert->removeUser(user);
      ar.update(*alert);
      ret = true;
    }
    else {
      _logger.err() << "No such user: " << userId << std::endl;
      this->returnCode(response, User_NotFound);
    }
  }
  else {
    _logger.err() << "No such alert: " << alertId << std::endl;
    this->returnCode(response, Alert_NotFound);
  }
  return (ret);
}

bool			RequestHandler::addTimeSlot(Json::Value const &request, Json::Value &response) {
  bool			ret = false;
  Repository<Profile>			pr(_database);
  Repository<Profile>::id_type		profileId = request["profileId"].asUInt64();
  Repository<Profile>::pointer_type	profile = pr.getById(profileId);

  if (profile) {
    Repository<TimeSlot>		tsr(_database);
    Json::Value const			&beg = request["beg"];
    Json::Value const			&end = request["end"];
    TimeSlot				ts(Week::Point(Week::toWeekDay(beg["day"].asUInt()), beg["minute"].asUInt()),
					   Week::Point(Week::toWeekDay(end["day"].asUInt()), end["minute"].asUInt()),
					   profile);

    if (true) { // There should be a check to see if the timeSlot doesn't overlaps on another one
      Repository<TimeSlot>::id_type	id = tsr.persist(ts);

      response["id"] = static_cast<Json::UInt64>(id);
      ret = true;
    }
    else {
      // Invalid TimeSlot
    }
  }
  else {
    this->returnCode(response, Profile_NotFound);
  }
  return (ret);
}

bool			RequestHandler::updateTimeSlot(Json::Value const &request, Json::Value &response) {
  bool			ret = false;
  Repository<TimeSlot>			tsr(_database);
  Repository<TimeSlot>::id_type		id = request["id"].asUInt64();
  Repository<TimeSlot>::pointer_type	timeSlot = tsr.getById(id);

  if (timeSlot) {
    Json::Value const			&beg = request["beg"];
    Json::Value const			&end = request["end"];

    timeSlot->setBeg(Week::Point(Week::toWeekDay(beg["day"].asUInt()), beg["minute"].asUInt()));
    timeSlot->setEnd(Week::Point(Week::toWeekDay(end["day"].asUInt()), end["minute"].asUInt()));
    
    if (true) { // There should be a check to see if the timeSlot doesn't overlaps on another one
      tsr.update(*timeSlot);
      ret = true;
    }
    else {
      // Invalid TimeSlot
    }
  }
  else {
    this->returnCode(response, TimeSlot_NotFound);
  }
  return (ret);
}

bool			RequestHandler::deleteTimeSlot(Json::Value const &request, Json::Value &response) {
  bool			ret = false;
  Repository<TimeSlot>			tsr(_database);
  Repository<TimeSlot>::id_type		id = request["id"].asUInt64();
  Repository<TimeSlot>::pointer_type	timeSlot = tsr.getById(id);

  if (timeSlot) {
    tsr.erase(*timeSlot);
    ret = true;
  }
  else {
    _logger.err() << "No such TimeSlot: " << id << std::endl;
    this->returnCode(response, TimeSlot_NotFound);
  }
  return (ret);
}

/*
** Return methods
*/

std::string const	&RequestHandler::returnCodeKey		= "returnCode";
std::string const	&RequestHandler::returnCodeStringKey	= "returnCodeString";

void			RequestHandler::returnCode(Json::Value &response, eReturnCode const &code) {
  std::ostringstream	oss;

  response[returnCodeKey] = code;
  oss << std::hex << std::showbase << code;
  response[returnCodeStringKey] = oss.str(); /* Makes it easier to debug */
}
