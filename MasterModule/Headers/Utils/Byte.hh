//
// Byte.hh for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb 23 00:06:04 2015 alexis mestag
// Last update Mon Feb 23 04:02:17 2015 alexis mestag
//

#ifndef		__BYTE_HH__
# define	__BYTE_HH__

# include	<array>
# include	<sstream>

namespace	Byte {

  template<typename T>
  static T		swap(T value) {
    unsigned int	bytes = sizeof(T);
    int			byte;
    T			ret = 0;

    for (unsigned int offset = 0; offset < bytes; ++offset) {
      byte = (value & (0xff << 8 * (bytes - (offset + 1)))) >> (8 * (bytes - (offset + 1)));
      ret |= byte << (8 * offset);
    }
    return (ret);
  }
}

#endif
