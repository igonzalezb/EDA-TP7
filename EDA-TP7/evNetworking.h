#pragma once
#include "servidor.h"
#include "cliente.h"
#include <iostream>
#include "GenericEvent.h"
#include "PackageMaker.h"
class evNetworking
{
public:
	evNetworking(servidor * server);
	evNetworking(cliente * client);
	~evNetworking();
	GenericEvent * hayEvento();
	bool SendData(char * buff, size_t buffSize);
private:
	PackageMaker pM;
	servidor * server;
	cliente * client;
	bool isServer;

};

