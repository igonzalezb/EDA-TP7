#pragma once
#include <boost\circular_buffer.hpp>
#include "GenericEvent.h"
#include "evNetworking.h"
#include "FileManager.h"
#include "PackageMaker.h"


#include "timeOut.h"

#include "evKeyboard.h"


class usefulInfo
{
public:
	usefulInfo(evNetworking * Net);
	~usefulInfo();
	boost::circular_buffer <GenericEvent *> buff;
	evNetworking * Net;
	DataPacket * File;
	PackageMaker makerDecoder;
	
	char lastDataSend[600];
	unsigned int sizeLastDataSend;
	bool isLastAck;
	timeOut Tout;
	KeyBoard Kboard;
	
private:
	
};

