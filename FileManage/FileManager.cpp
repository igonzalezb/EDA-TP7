#include "FileManager.h"


DataPacket::DataPacket(std::string name, bool isReadMode)
{
	this->isReadMode = isReadMode;
	
	if(isReadMode)
	{
		archivo->open(name, std::fstream::in);
	}
	else
	{
		archivo->open(name, std::fstream::out);
	}

}

DataPacket::~DataPacket()
{
	archivo->close();
}