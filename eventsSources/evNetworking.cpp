#include "evNetworking.h"
#include "TPTF_Events.h"
#define SIZE_BUFF 600

void copyCharAtoB(char * a, char * b, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		b[i] = a[i];
	}
}

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
	GenericEvent * ev = NULL;
	int tempCounter = 0;
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

		switch (pM.getTypePackage(tempBuff, dataRecive))
		{
		case _RRQ_:
			ev = new Rrq(dataRecive);
			copyCharAtoB(tempBuff, ((Rrq *)ev)->getPackage(&tempCounter),dataRecive);
			break;
		case _WRQ_:
			ev = new Wrq(dataRecive);
			copyCharAtoB(tempBuff, ((Wrq *)ev)->getPackage(&tempCounter), dataRecive);
			break;
		case _DATA_:
			ev = new Data(dataRecive);
			copyCharAtoB(tempBuff, ((Data *)ev)->getPackage(&tempCounter), dataRecive);
			break;
		case _ACK_:
			ev = new Ack(dataRecive);
			copyCharAtoB(tempBuff, ((Ack *)ev)->getPackage(&tempCounter), dataRecive);
			break;
		case _ERROR_:
			ev = new Error(dataRecive);
			copyCharAtoB(tempBuff, ((Error *)ev)->getPackage(&tempCounter), dataRecive);
			break;
		case _LASTDATA_:
			ev = new LastData(dataRecive);
			copyCharAtoB(tempBuff, ((LastData *)ev)->getPackage(&tempCounter), dataRecive);
			break;
		}
		//ver el last data

	}
	else
	{
		ev=NULL;
	}
	return ev;
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

