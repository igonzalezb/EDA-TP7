#include "FileManager.h"


DataPacket::DataPacket(std::string name, bool isReadMode)
{
	this->isReadMode = isReadMode;
	
	if(isReadMode)
	{
		archivo->open(name, std::fstream::in | std::fstream::binary);
	}
	else
	{
		archivo->open(name, std::fstream::out | std::fstream::binary);
	}

}

DataPacket::~DataPacket()
{
	archivo->close();
}