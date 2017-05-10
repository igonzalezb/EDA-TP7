#pragma once

#include <string>
#include <fstream>

class DataPacket
{
public:
	DataPacket(std::string name, bool isReadMode);
	~DataPacket();

	//void makeDataPacket(char* a, int size);
	//void createFrom;

private:
	std::fstream* archivo;
	bool isReadMode;
};
