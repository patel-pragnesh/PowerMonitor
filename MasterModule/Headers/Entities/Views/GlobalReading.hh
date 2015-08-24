//
// GlobalReading.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Aug 24 23:10:16 2015 alexis mestag
// Last update Mon Aug 24 23:47:29 2015 alexis mestag
//

#ifndef		__GLOBALREADING_HH__
# define	__GLOBALREADING_HH__

# include	"Entities/Reading.hh"

struct	GlobalReading
{
  Time::Point	tp;
  double	value;
};

# ifdef	ODB_COMPILER
#  pragma db view (GlobalReading) object(Reading) //object(Information = info: Reading::_info)
#  pragma db member(GlobalReading::tp) column(Reading::_tp)
#  pragma db member(GlobalReading::value) column("SUM(info_value)")
# endif

#endif
