//
// daytime.7.cpp for daytime.7 in /home/mestag_a/Documents/Projets/EIP/MasterModule/Tests/Boost.Asio
// 
// Made by alexis mestag
// Login   <mestag_a@epitech.net>
// 
// Started on  Mon Jan 26 00:35:35 2015 alexis mestag
// Last update Mon Jan 26 00:40:09 2015 alexis mestag
//

#include	<array>
#include	<chrono>
#include	<iostream>
#include	<memory>
#include	<string>
#include	<boost/asio.hpp>
#include	<boost/bind.hpp>

using		boost::asio::ip::tcp;
using		boost::asio::ip::udp;

class		TCPConnection : public std::enable_shared_from_this<TCPConnection>
{
public:
  typedef std::shared_ptr<TCPConnection>	pointer;

private:
  tcp::socket	_socket;
  std::string	_msg;
  
public:
  static pointer	create(boost::asio::io_service &io) {
    return (pointer(new TCPConnection(io)));
  }

private:
  TCPConnection(boost::asio::io_service &io)
    : _socket(io) {
  }

public:
  ~TCPConnection() {}

public:
  void			start() {
    _msg = this->makeDaytimeString();

    boost::asio::async_write(_socket, boost::asio::buffer(_msg),
			     boost::bind(&TCPConnection::handleWrite,
					 this->shared_from_this()));
  }

  tcp::socket		&socket() {
    return (_socket);
  }
  
private:
  void			handleWrite() {
  }

  std::string		makeDaytimeString() {
    std::chrono::system_clock::time_point	tp = std::chrono::system_clock::now();
    std::time_t tt = std::chrono::system_clock::to_time_t(tp);

    return (std::ctime(&tt));
  }

};

class		TCPServer
{
private:
  tcp::acceptor	_acceptor;

public:
  TCPServer(boost::asio::io_service &io)
    : _acceptor(io, tcp::endpoint(tcp::v4(), 13)) {
    this->startAccept();
  }
  ~TCPServer() {}

private:
  void		startAccept() {
    TCPConnection::pointer	newConnection = TCPConnection::create(_acceptor.get_io_service());

    _acceptor.async_accept(newConnection->socket(),
			   boost::bind(&TCPServer::handleAccept,
				       this, newConnection,
				       boost::asio::placeholders::error));
  }

  void		handleAccept(TCPConnection::pointer newConnection,
			     boost::system::error_code const &ec) {
    if (!ec) {
      newConnection->start();
    }

    this->startAccept();
  }
};

class		UDPServer
{
private:
  udp::socket		_socket;
  udp::endpoint		_remote_endpoint;
  std::array<char, 1>	_recv_buf;

public:
  UDPServer(boost::asio::io_service &io)
    : _socket(io, udp::endpoint(udp::v4(), 13)) {
    this->startReceive();
  }

  ~UDPServer() {}

private:
  void		startReceive() {
    _socket.async_receive_from(boost::asio::buffer(_recv_buf), _remote_endpoint,
			       boost::bind(&UDPServer::handleReceive, this,
					   boost::asio::placeholders::error,
					   boost::asio::placeholders::bytes_transferred));
  }

  void		handleReceive(boost::system::error_code const &ec, std::size_t) {
    if (!ec || ec == boost::asio::error::message_size) {
      std::shared_ptr<std::string>	msg(new std::string(this->makeDaytimeString()));

      _socket.async_send_to(boost::asio::buffer(*msg), _remote_endpoint,
			    boost::bind(&UDPServer::handleSend, this, msg,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
      this->startReceive();
    }
  }

  void		handleSend(std::shared_ptr<std::string>,
			   boost::system::error_code const &,
			   std::size_t) {
  }
  
private:
  std::string	makeDaytimeString() {
    std::chrono::system_clock::time_point	tp = std::chrono::system_clock::now();
    std::time_t tt = std::chrono::system_clock::to_time_t(tp);

    return (std::ctime(&tt));
  }
};

int		main() {
  try {
    boost::asio::io_service	io;
    TCPServer			tcpServer(io);
    UDPServer			udpServer(io);

    io.run();
  }
  catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return (1);
  }
  return (0);
}
