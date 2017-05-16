#include "ClientStates.h"
#include "TPTF_Events.h"



GenericState* Reading :: onData (GenericEvent * event)
{
	int Size = 0;
	unsigned int sizeAck = 0;
	char buff[600];
	//"store data, send ACK"
	((Data *)event)->getPackage(&Size);
	for (size_t i = 0; i < Size; i++)
	{
		buff[i] = (((Data *)event)->getPackage(&Size))[i];
	}

	//store data in file
	((usefulInfo *)(((Data *)event)->UInfo))->File->SaveDATA(((Data *)event)->getPackage(&Size),Size);
	//make ack, and store it in buff.
	((usefulInfo *)(((Data *)event)->UInfo))->makerDecoder.makeACK(buff, sizeAck);
	//send the ACK package to server
	((usefulInfo *)(((Data *)event)->UInfo))->Net->SendData(buff, sizeAck);
	

	
	return NULL;
}

GenericState* Reading :: onLastData (GenericEvent * event)
{
	
	//"store data, send LAST ACK, end connection"
	int Size = 0;
	unsigned int sizeAck = 0;
	char buff[600];
	//"store data, send ACK"
	((LastData *)event)->getPackage(&Size);
	for (size_t i = 0; i < Size; i++)
	{
		buff[i] = (((LastData *)event)->getPackage(&Size))[i];
	}
	//store data in file
	((usefulInfo *)(((LastData *)event)->UInfo))->File->SaveDATA(((LastData *)event)->getPackage(&Size), Size);
	//make ack, and store it in buff.
	((usefulInfo *)(((LastData *)event)->UInfo))->makerDecoder.makeACK(buff, sizeAck);
	//send the ACK package to server
	((usefulInfo *)(((LastData *)event)->UInfo))->Net->SendData(buff, sizeAck);
	((usefulInfo *)(((LastData *)event)->UInfo))->File->~DataPacket();
	return NULL;
}

GenericState* Reading :: onTimeout(GenericEvent * event)
{
	unsigned int sizeAck = 0;
	char buff[600];
	//reset asck
	//make ack, and store it in buff.
	((usefulInfo *)(((Timeout *)event)->UInfo))->makerDecoder.makeACK(buff, sizeAck);
	//send the ACK package to server
	((usefulInfo *)(((Timeout *)event)->UInfo))->Net->SendData(buff, sizeAck);
	//"resend ACK (once per data block)"
	
	return NULL;
}

GenericState* Reading :: onError (GenericEvent * event)
{
	exit(4);
	//"end connection and shutdown"
	return NULL;
}

GenericState* Reading :: onExit (GenericEvent * event)
{
	exit(4);
	//"end connection and shut down"
	return NULL;
}


GenericState* Writing :: onAck(GenericEvent * event)
{
	char buff[600];
	unsigned int sizeData = 0;
	//make package data, store it in de buff
	((usefulInfo *)(((Ack *)event)->UInfo))->File->ReadDATA(buff, sizeData);
	//back up of last data sended
	for (size_t i = 0; i < sizeData; i++)
	{
		(((usefulInfo *)(((Ack *)event)->UInfo))->lastDataSend)[i] = buff[i];

	}
	//save size of last data sended
	(((usefulInfo *)(((Ack *)event)->UInfo))->sizeLastDataSend) = sizeData;
	//send data
	(((usefulInfo *)(((Ack *)event)->UInfo)))->Net->SendData(buff, sizeData);
	
	if (((((usefulInfo *)(((Ack *)event)->UInfo)))->makerDecoder.getTypePackage(buff, sizeData)) == _LASTDATA_)
	{
		(((usefulInfo *)(((Ack *)event)->UInfo)))->isLastAck = true;
	}
	
	return NULL;
}

GenericState* Writing :: onLastAck (GenericEvent * event)
{
	
	exit(4);
	//"end connection and shut down"
	return NULL;
}

GenericState* Writing :: onTimeout(GenericEvent * event)
{
	
	//"resend data (only once per data block)"
	//decrement block number
	//resend last data sended
	(((usefulInfo *)(((Timeout *)event)->UInfo)))->Net->SendData((((usefulInfo *)(((Timeout *)event)->UInfo)))->lastDataSend, (((usefulInfo *)(((Timeout *)event)->UInfo)))->sizeLastDataSend);
	return NULL;
}

GenericState* Writing :: onError (GenericEvent * event)
{
	exit(4);
	//"end connection and shut down"
	return NULL;
}

GenericState* Writing :: onExit (GenericEvent * event)
{
	exit(4);
	//"end connection and shut down"
	return NULL;
}
