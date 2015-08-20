//
// JsonValidator.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule/Tests
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Sun Feb 22 18:26:11 2015 alexis mestag
// Last update Sat Jul 11 22:09:17 2015 alexis mestag
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

  template<typename Fn> JsonValidator(Fn &&fn) : _predicate(std::forward<Fn>(fn)) {}
  JsonValidator(std::initializer_list<pair_type> const &il);

  JsonValidator		&operator=(JsonValidator const &rhs) = default;
  
  ~JsonValidator() = default;

public:
  bool			operator()(Json::Value const &json) const;

public:
  static bool		isNonEmptyString(Json::Value const &json);
};

#endif
