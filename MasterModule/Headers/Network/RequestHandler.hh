//
// RequestHandler.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb  9 02:24:18 2015 alexis mestag
// Last update Sat Jun 20 21:47:42 2015 alexis mestag
//

#ifndef			__REQUESTHANDLER_HH__
# define		__REQUESTHANDLER_HH__

# include		<algorithm>
# include		<memory>

# include		<json/value.h>

# include		"Database/Repository.hpp"
# include		"Entities/Entity.hh"
# include		"Entities/Session.hh"
# include		"Utils/Logger.hh"

class			RequestHandler
{
public:
  enum			eReturnCode {
    Ok					= 0,
    Generic_NotWellFormattedRequest	= 0x101,
    Generic_CommandNotFound		= 0x102,
    Generic_InvalidSession		= 0x103,
    Generic_SessionExpired		= 0x104,

    Authentication_IncorrectPassword	= 0x201,

    User_NotFound			= 0x301,
    User_InvalidPassword		= 0x302,

    Module_NotFound			= 0x401,
    Module_CannotUpdateState		= 0x402,
    Module_AlreadyInGivenState		= 0x403,

    Profile_NotFound			= 0x501,
    Profile_StillInUse			= 0x502,
    Profile_NameAlreadyExists		= 0x503,

    Alert_NotFound			= 0x601,

    TimeSlot_NotFound			= 0x701,

    Unit_NotFound			= 0x801,
  };

private:
  static std::string const	&returnCodeKey;
  static std::string const	&returnCodeStringKey;

private:
  Database			&_database;
  Logger			&_logger;
  std::shared_ptr<Session>	_session;

public:
  RequestHandler() = delete;

  RequestHandler(Database &Database, Logger &logger);
  RequestHandler(RequestHandler const &rhs) = default;
  RequestHandler	&operator=(RequestHandler const &rhs) = default;

  ~RequestHandler() = default;

public:
  bool			handle(Json::Value const &request, Json::Value &response);
  void			persistSession();

private:
  template<typename T>
  bool			getEntities(std::string const &key, Json::Value const &, Json::Value &response) {
    static_assert(std::is_base_of<Entity, T>::value, "T must be a descendant of Entity");

    Repository<T>			r(_database);
    typename Repository<T>::result_type	entities = r.getAll();
    Json::Value				array(Json::ValueType::arrayValue);

    std::for_each(entities.begin(), entities.end(), [&](T const &entity) {
	Json::Value			value(Json::ValueType::objectValue);

	entity.serialize(value);
	array.append(value);
      });
    response[key] = array;
    return (true);  
  }

  template<typename T>
  bool			getEntity(std::string const &key, eReturnCode const &retCode,
				  Json::Value const &request, Json::Value &response) {
    static_assert(std::is_base_of<Entity, T>::value, "T must be a descendant of Entity");

    Repository<T>				r(_database);
    typename Repository<T>::id_type		id = request["id"].asUInt64();
    typename Repository<T>::pointer_type	entity = r.getById(id);
    bool					ret = false;

    if (entity) {
      entity->serialize(response[key]);
      ret = true;
    }
    else {
      this->returnCode(response, retCode);
    }    
    return (ret);
  }

  bool			cmdHandler(Json::Value const &request, Json::Value &response);

  /* Authentication */
  bool			isAuthenticated(Json::Value const &request, Json::Value &response);
  bool			login(Json::Value const &request, Json::Value &response);

  /* Users */
  bool			changePassword(Json::Value const &request, Json::Value &response);
  
  /* Modules */
  bool			getModule(Json::Value const &request, Json::Value &response);
  bool			getModules(Json::Value const &request, Json::Value &response);
  bool			turnOnOff(Json::Value const &request, Json::Value &response);
  bool			renameModule(Json::Value const &request, Json::Value &response);
  bool			updateModuleDefaultProfile(Json::Value const &request, Json::Value &response);
  bool			getModuleConso(Json::Value const &request, Json::Value &response);

  /* Profiles */
  bool			getProfile(Json::Value const &request, Json::Value &response);
  bool			getProfiles(Json::Value const &request, Json::Value &response);
  bool			addProfile(Json::Value const &request, Json::Value &response);
  bool			deleteProfile(Json::Value const &request, Json::Value &reponse);
  bool			updateProfilePolling(Json::Value const &request, Json::Value &response);

  /* Alerts */
  bool			addAlert(Json::Value const &request, Json::Value &response);
  bool			updateAlert(Json::Value const &request, Json::Value &response);
  bool			deleteAlert(Json::Value const &request, Json::Value &response);
  bool			addAlertUser(Json::Value const &request, Json::Value &response);
  bool			deleteAlertUser(Json::Value const &request, Json::Value &response);

  /* TimeSlots */
  bool			addTimeSlot(Json::Value const &request, Json::Value &response);
  bool			updateTimeSlot(Json::Value const &request, Json::Value &response);
  bool			deleteTimeSlot(Json::Value const &request, Json::Value &response);
  
  /* Return */
  void			returnCode(Json::Value &reponse, eReturnCode const &code);
};

#endif
