#include "FIleManager.h"



DataPacket::DataPacket(std::string name, bool isReadMode)
{
	this->isReadMode = isReadMode;
	this->sizeDATA = 0;

	if (isReadMode)
	{
		archivo.open(name, std::fstream::in | std::fstream::binary);
	}
	else
	{
		archivo.open(name, std::fstream::out | std::fstream::binary);
	}

}

DataPacket::~DataPacket()
{
	archivo.close();
}

bool DataPacket::ReadDATA(char * Package, unsigned int & sizePackage)
{
	char c;

	for (sizeDATA=0; (sizeDATA<MaxSizeDATA)&&(archivo.good() && archivo.get(c));sizeDATA++)
	{
		DATA[sizeDATA] = c;
	}

	P.makeDATA(Package, DATA, sizeDATA, sizePackage);

	return true;
}


bool DataPacket::SaveDATA(char * Package, unsigned int sizePackage)
{

	P.decodeDATA(DATA, Package, sizePackage, sizeDATA);

	for (unsigned int i = 0; (i<sizeDATA)&& (archivo.good()); i++)
	{
		archivo.put(DATA[i]);
		
	}
	

	return true;

}