#include "FileManager.h"


DataPacket::DataPacket(std::string name, bool isReadMode)
{
	this->isReadMode = isReadMode;
	this->BytesRead = 0;

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

void DataPacket::ReadDATA()
{
	char c;


	for (BytesRead=0; (archivo->good() && archivo->get(c));BytesRead++)
	{
		ArrayOfReadDATA[BytesRead] = c;
	}


}
