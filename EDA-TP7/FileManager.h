#pragma once

#include <string>
#include <fstream>

class DataPacket
{
public:

	DataPacket(std::string name, bool isReadMode);
	~DataPacket();

	void ReadDATA();

private:

	int BytesRead; //cantidad de bytes leidos
	std::fstream* archivo;
	bool isReadMode;
	char* ArrayOfReadDATA;
};
