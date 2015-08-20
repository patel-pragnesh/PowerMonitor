//
// ByteArray.hpp for PowerMonitor in /home/mestag_a/Documents/Projets/EIP/MasterModule
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Feb 23 03:37:18 2015 alexis mestag
// Last update Mon Feb 23 22:44:56 2015 alexis mestag
//

#ifndef			__BYTEARRAY_HH__
# define		__BYTEARRAY_HH__

# include		<array>
# include		<iostream>
# include		<iomanip>
# include		<sstream>
# include		<string>

# include		<cryptopp/hex.h>

template<size_t N>
class			ByteArray
{
public:
  typedef unsigned char		byte;
  typedef std::array<byte, N>	type;

private:
  type			_array;
  std::string		_hex;

public:
  ByteArray() = default;
  ByteArray(type const &array) { this->setArray(array); }
  ByteArray(std::string const &hex) { this->setHexString(hex); }
  ~ByteArray() = default;

public:
  type			&getArray() {
    return (_array);
  }
  type const		&getArray() const {
    return (_array);
  }
  void			setArray(type const &array) {
    _array = array;
    _hex = encode(array);
  }

  std::string const	&toHexString() const {
    return (_hex);
  }
  void			setHexString(std::string const &hex) {
    _hex = hex;
    for (unsigned int i = 0; i < _array.size(); ++i) {
      std::string sub = hex.substr(i * 2, 2);
      _array[i] = (unsigned char)std::stoi(sub, 0, 16);
    }
  }

  static std::string	encode(std::array<byte, N> const &array) {
    CryptoPP::HexEncoder	encoder(nullptr, false);
    std::string			encoded;

    encoder.Put(array.data(), array.size() * sizeof(byte));
    encoder.MessageEnd();

    encoded.resize(encoder.MaxRetrievable());
    encoder.Get((byte *)encoded.data(), encoded.size());
    return (encoded);
  }

};

#endif
