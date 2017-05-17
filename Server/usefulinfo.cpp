#include "usefulinfo.h"


usefulInfo::usefulInfo(evNetworking * Net):buff(600)
{
	this->Net = Net;
	sizeLastDataSend = 0;
	isLastAck = false;
}

usefulInfo::~usefulInfo()
{
}
