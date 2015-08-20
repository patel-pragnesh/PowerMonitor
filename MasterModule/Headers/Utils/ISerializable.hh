//
// ISerializable.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Feb 10 17:09:41 2015 alexis mestag
// Last update Tue Feb 10 17:13:09 2015 alexis mestag
//

#ifndef			__ISERIALIZABLE_HH__
# define		__ISERIALIZABLE_HH__

# include		<json/value.h>

class			ISerializable
{
public:
  virtual ~ISerializable() = default;

public:
  virtual void		serialize(Json::Value &json) const = 0;
};

#endif
