#include "evNetworking.h"
#define SIZE_BUFF 600


evNetworking::evNetworking(servidor * server)
{
	this->server = server;
	client = NULL;
	isServer = true;
}

evNetworking::evNetworking(cliente * client)
{
	this->client = client;
	server = NULL;
	isServer = false;
}

evNetworking::~evNetworking()
{
	if (isServer)
	{
		server->~servidor();
	}
	else
	{
		client->~cliente();
	}
}

GenericEvent * evNetworking::hayEvento()
{
	char tempBuff[SIZE_BUFF];
	size_t dataRecive = 0;
	if (isServer)
	{
		dataRecive = server->nonBlockinReceiveDataForCliente(tempBuff, SIZE_BUFF);
	}
	else
	{
		dataRecive = client->nonBlockinReceiveDataForServer(tempBuff, SIZE_BUFF);
	}
	
	if (dataRecive > 0)
	{
		//switch case con el tipo y genero el paquete
		//devuelvo el paquete data
	}
	else
	{
		return NULL;
	}
}

bool evNetworking::SendData(char * buff, size_t buffSize)
{
	if (isServer)
	{
		return (server->sendData(buff, buffSize));
	}
	else
	{
		return (client->sendData(buff, buffSize));
	}
	
}
