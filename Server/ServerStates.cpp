#include "ServerStates.h"
#include "TPTF_Events.h"
#include "FileManager.h"
#include "PackageMaker.h"
#include "usefulinfo.h"
using namespace std;

GenericState* Idle::onRrq(GenericEvent * event)
{
	char Package[600];
	unsigned int sizeData = 0;
	int siezDataInt = 0;
	//"start connection with client, send first data block"
	//abro el archivo y lo almaceno en usefulinfo
	(((usefulInfo *)(((Rrq *)event)->UInfo))->File)= new DataPacket((((Rrq *)event)->getPackage(&siezDataInt) + 2), true);
	//tomo data del arechivo y armo paquete Data
	(((usefulInfo *)(((Rrq *)event)->UInfo))->File)->ReadDATA(Package, sizeData);
	//envio el paquete data al cliente
	(((usefulInfo *)(((Rrq *)event)->UInfo))->Net)->SendData(Package, sizeData);
	return new Reading();

}

GenericState* Idle::onWrq(GenericEvent * event)
{
	int sizeData = 0;
	unsigned int sizeAck = 0;
	char Package[600];
	(((usefulInfo *)(((Wrq *)event)->UInfo))->File) = new DataPacket((((Wrq *)event)->getPackage(&sizeData) + 2), false);
	//"start connection with client"
	//creo y almaceno un ack en package
	((usefulInfo *)(((Wrq *)event)->UInfo))->makerDecoder.makeACK(Package, sizeAck);
	//envio ack a client
	((usefulInfo *)(((Wrq *)event)->UInfo))->Net->SendData(Package, sizeAck);
	return new Writing();
}

GenericState* Idle::onExit(GenericEvent * event)
{
	 
	//"shut down
	exit(4);
	return NULL;
}


GenericState* Writing :: onData (GenericEvent * event)
{
     
    //"store data, send 
	int Size = 0;
	unsigned int SizeAck = 0;
	char * buff = NULL;
	char buffTemp[600];
	//store data
	buff = ((Data *)event)->getPackage(&Size);
	(((usefulInfo *)(((Data *)event)->UInfo))->File)->SaveDATA(buff, Size);
	//envio ack al cliente
	((usefulInfo *)(((Data *)event)->UInfo))->makerDecoder.makeACK(buffTemp,SizeAck);
	((usefulInfo *)(((Data *)event)->UInfo))->Net->SendData(buffTemp, SizeAck);




    return NULL;
}

GenericState* Writing :: onLastData (GenericEvent * event)
{
     
    //"store data, send LAST_ACK, end connection" 
	//"store data, send 
	int Size = 0;
	unsigned int SizeAck = 0;
	char * buff = NULL;
	char buffTemp[600];
	//store data
	buff = ((LastData *)event)->getPackage(&Size);
	(((usefulInfo *)(((LastData *)event)->UInfo))->File)->SaveDATA(buff, Size);
	(((usefulInfo *)(((LastData *)event)->UInfo))->File)->~DataPacket();
	//envio ack al cliente
	((usefulInfo *)(((LastData *)event)->UInfo))->makerDecoder.makeACK(buffTemp, SizeAck);
	((usefulInfo *)(((LastData *)event)->UInfo))->Net->SendData(buffTemp, SizeAck);
    return new Idle();
}

GenericState* Writing :: onTimeout(GenericEvent * event)
{
	unsigned int SizeAck = 0;
	char buffTemp[600];
	//NO IMCREMENTAR CONTADOR DE ACK
    //"resend ACK (only once per data block)"
	((usefulInfo *)(((LastData *)event)->UInfo))->makerDecoder.makeACK(buffTemp, SizeAck);
	((usefulInfo *)(((LastData *)event)->UInfo))->Net->SendData(buffTemp, SizeAck);
    return NULL;
}

GenericState* Writing :: onError (GenericEvent * event)
{
     
    //"end connection"
    return new Idle();
}

GenericState* Writing :: onExit (GenericEvent * event)
{
	exit(4);
    //"end connection and shut down"    
    return NULL;
}


GenericState* Reading :: onAck(GenericEvent * event)
{
     
    //"send data
	char Package[600];
	unsigned int sizeData = 0;
	//tomo data del arechivo y armo paquete Data
	(((usefulInfo *)(((Ack *)event)->UInfo))->File)->ReadDATA(Package, sizeData);
	//envio el paquete data al cliente
	(((usefulInfo *)(((Ack *)event)->UInfo))->Net)->SendData(Package, sizeData);
	for (size_t i = 0; i < sizeData; i++)
	{
		(((usefulInfo *)(((Ack *)event)->UInfo))->lastDataSend)[i] = Package[i];
	}
	((usefulInfo *)(((Ack *)event)->UInfo))->sizeLastDataSend = sizeData;
	if ((((usefulInfo *)(((Ack *)event)->UInfo))->makerDecoder.getTypePackage(Package, sizeData)) == _LASTDATA_)
	{
		((usefulInfo *)(((Ack *)event)->UInfo))->isLastAck = true;
	}
    return NULL;
}

GenericState* Reading :: onLastAck (GenericEvent * event)
{
	((usefulInfo *)(((LastAck *)event)->UInfo))->isLastAck = false;
   //"end connection");
    return new Idle();
}

GenericState* Reading :: onTimeout(GenericEvent * event)
{
     
   //"resend data (only once per data block)"
	(((usefulInfo *)(((Timeout *)event)->UInfo))->Net)->SendData((((usefulInfo *)(((Timeout *)event)->UInfo))->lastDataSend), ((usefulInfo *)(((Timeout *)event)->UInfo))->sizeLastDataSend);
    return NULL;
}

GenericState* Reading :: onError (GenericEvent * event)
{
     
   //"end connection");
    return new Idle();
}

GenericState* Reading :: onExit (GenericEvent * event)
{
	exit(4);
   //"end connection and shut down"
    return NULL;
}