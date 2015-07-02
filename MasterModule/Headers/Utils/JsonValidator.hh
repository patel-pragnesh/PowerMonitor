//
// JsonValidator.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule/Tests
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Feb 22 18:26:11 2015 alexis mestag
// Last update Sun Mar 29 18:22:33 2015 alexis mestag
//

#ifndef			__JSONVALIDATOR_HH__
# define		__JSONVALIDATOR_HH__

# include		<functional>
# include		<initializer_list>
# include		<map>

# include		<json/value.h>

class			JsonValidator
{
public:
  typedef std::map<std::string, JsonValidator>		map_type;
  typedef map_type::value_type				pair_type;
  typedef std::function<bool(Json::Value const &)>	predicate;

private:
  predicate		_predicate;
  map_type		_members;

public:
  JsonValidator() = default;
  JsonValidator(JsonValidator const &rhs) = default;

  template<typename Fn> JsonValidator(Fn fn) : _predicate(fn) {}
  JsonValidator(std::initializer_list<pair_type> const &il);

  JsonValidator		&operator=(JsonValidator const &rhs) = default;
  
  ~JsonValidator() = default;

public:
  bool			operator()(Json::Value const &json) const;

public:
  static bool		isNonEmptyString(Json::Value const &json);
};

#endif
