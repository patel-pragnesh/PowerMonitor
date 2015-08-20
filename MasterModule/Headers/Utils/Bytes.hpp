//
// Bytes.hpp for PowerMonitor in /home/mestag_a/Documents/Projets/ODB
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon May  4 03:59:14 2015 alexis mestag
// Last update Mon May  4 05:29:43 2015 alexis mestag
//

#ifndef			__BYTES_HPP__
# define		__BYTES_HPP__

# include		<array>
# include		<cstdlib>
# include		<iomanip>
# include		<ios>
# include		<iostream>
# include		<sstream>
# include		<utility>

namespace		Bytes
{
  using byte		= unsigned char;

  template<std::size_t N>
  std::string		hexEncode(std::array<byte, N> const &array) {
    std::ostringstream	oss;

    oss << std::hex;
    for (auto const &b: array) {
      oss << std::setw(2) << std::setfill('0') << static_cast<int>(b);
    }

    return (oss.str());
  }

  template<std::size_t N>
  void			hexDecode(std::string const &str, std::array<byte, N> &out) {
    char		hexByte[3];

    hexByte[sizeof(hexByte) - 1] = 0;
    for (unsigned int i = 0; i < N; ++i) {
      hexByte[0] = str[i * 2];
      hexByte[1] = str[i * 2 + 1];
      out[i] = strtoul(hexByte, NULL, 16);
    }
  }
  
  template<typename T>
  T			swap(T const &o) {
    unsigned int	size = sizeof(T);
    unsigned int	midSize = size / 2;
    union		{
      T			value;
      byte		bytes[sizeof(T)];
    }			u = {o};

    for (unsigned int i = 0; i < midSize; ++i) {
      std::swap(u.bytes[i], u.bytes[size - 1 - i]);
    }
    return (u.value);
  }
}

#endif
