//
// Logger.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule/Unit tests/c++
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Wed Apr 15 16:39:06 2015 alexis mestag
// Last update Wed Apr 15 17:04:53 2015 alexis mestag
//

#ifndef			__LOGGER_HH__
# define		__LOGGER_HH__

# include		<ostream>

class			Logger
{
private:
  std::ostream		&_out;
  std::ostream		&_err;
  std::string		_header;

public:
  Logger();
  ~Logger() = default;

public:
  void			setHeader(std::string const &header);
  std::ostream		&log(std::ostream &os);
  std::ostream		&out();
  std::ostream		&err();
};

#endif
