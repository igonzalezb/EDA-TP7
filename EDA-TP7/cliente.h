#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#define MY_ERROR -1
#define MY_EMPTY 0
class cliente
{
public:
	cliente();
	~cliente();
	void ConectToServer(const char* ipServer="localhost", const char* portNumber="12345");
	bool sendData(char * dataToSend_t, unsigned int sizeData);
	size_t receiveDataForServidor(char * buffer_t, int bufferSize);
	size_t nonBlockinReceiveDataForServer(char * buffer_t, int bufferSize);
private:
	boost::asio::ip::tcp::resolver* clienteResolver;
	boost::asio::ip::tcp::socket* clienteSocket;
	boost::asio::ip::tcp::resolver::iterator endpoint;
	boost::asio::io_service* ioCliente;
};

