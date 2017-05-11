#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <cstdint>
#define MY_ERROR -1
#define MY_EMPTY 0


class servidor
{
public:
	servidor(UINT32 port=12345);
	~servidor();
	void waitForCliente();
	size_t receiveDataForCliente(char * buffer_t, int bufferSize);
	size_t nonBlockinReceiveDataForCliente(char * buffer_t, int bufferSize);
	bool sendData(char * dataToSend_t, unsigned int sizeData);
private:
	UINT32 portNumber;
	boost::asio::io_service*  ioServer;
	boost::asio::ip::tcp::socket* ServerSocket;
	boost::asio::ip::tcp::acceptor* conectionServerAceptor;

	boost::asio::ip::tcp::resolver::iterator endpoint;
	
};

