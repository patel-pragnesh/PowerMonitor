//
// Logger.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Tue Mar  3 20:04:11 2015 alexis mestag
// Last update Wed Mar  4 00:24:32 2015 alexis mestag
//

#ifndef			__LOGGER_HH__
# define		__LOGGER_HH__

# include		<ctime>
# include		<chrono>
# include		<iostream>

class			Logger
{
private:
  typedef std::chrono::system_clock	clock;

private:
  std::ostream		&_out;
  std::ostream		&_err;
  std::string		_header;
  
public:
  Logger(Logger const &rhs) = delete;
  Logger		operator=(Logger const &rhs) = delete;

  Logger();
  Logger(std::ostream &os);
  Logger(std::ostream &out, std::ostream &err);
  ~Logger() = default;

public:
  void			setHeader(std::string const &header);
  std::ostream		&log(std::ostream &os);
  std::ostream		&out();
  std::ostream		&err();
};

#endif
