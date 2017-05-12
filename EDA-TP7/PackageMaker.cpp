#include "PackageMaker.h"

bool PackageMaker::makeDATA (char* Package, char* data, unsigned int sizeData, unsigned int& sizePacket)
{

	Package[0] = 0x00;
	Package[1] = 0x03;

	Package[2] = (BlockNumber & 0xff00) >> 8;
	Package[3] = (BlockNumber & 0x00ff);


	for (unsigned int i = 4,j=0; j <= sizeData; j++,i++)
	{
		Package[i] = data[j];
	}


	sizePacket = sizeData + 4;


	return true;
}

bool PackageMaker::decodeDATA(char* DATA,char* DATApackage, unsigned int sizeDATApackage, unsigned int& sizeDATA)
{
	int j = 0;

	for (unsigned int i = 4; i < sizeDATApackage; j++, i++)
	{
		DATA[j] = DATApackage[i];
	}

	sizeDATA = j;

	return true;
}

bool PackageMaker::makeRRQ(char * Package,char* NombreTXT, unsigned int& sizePackage)
{
	Package[0] = 0x00;
	Package[1] = 0x01;

	int NameTXTsize = sprintf(&Package[2], "%s", NombreTXT);
	int ModeSize = sprintf(&Package[NameTXTsize + 2], "octet");

	sizePackage = 2 + NameTXTsize + ModeSize;

	return true;
}

bool PackageMaker::makeWRQ(char * Package, char* NombreTXT, unsigned int& sizePackage)
{

	Package[0] = 0x00;
	Package[1] = 0x02;

	int NameTXTsize = sprintf(&Package[2], "%s", NombreTXT);
	int ModeSize = sprintf(&Package[NameTXTsize + 2], "octet");

	sizePackage = 2 + NameTXTsize + ModeSize;

	return true;
}

void PackageMaker::setBlockNumber(int number)
{
	this->BlockNumber = number;
}

int PackageMaker::getBlockNumber()
{
	return BlockNumber;
}

void PackageMaker::incBlockNumber()
{ 
	BlockNumber++;
}

typePacket PackageMaker::getTypePackage(char * Package, unsigned int sizePackage)
{
	typePacket type = (typePacket)((Package[0] << 8) + Package[1]);


	unsigned int sizeDATA = (sizePackage - 4);

	switch (type)
	{
		case _DATA_:
			type = _DATA_;
			if (sizeDATA < 512)
			{
				type = _LASTDATA_;
			}
			break;
		case _RRQ_:_WRQ_:_DATA_:_ACK_:_ERROR_:
			return type;
			break;
	}

	return type;
}

PackageMaker::PackageMaker()
{
	BlockNumber = 1;
}

bool PackageMaker::makeACK(char* Package, unsigned int& sizePackage)
{
	Package[0] = 0x00;
	Package[1] = 0x04;

	Package[2] = (getBlockNumber() & 0xff00) >> 8;
	Package[3] = (getBlockNumber() & 0x00ff);

	incBlockNumber();

	sizePackage = 4;

	return true;
}

bool PackageMaker::makeERROR(char* Package, unsigned int error_code, char* error_msg, unsigned int& sizePackage)
{

	Package[0] = 0x00;
	Package[1] = 0x05;

	Package[2] = (error_code & 0xff00) >> 8;
	Package[3] = (error_code & 0x00ff);

	int sizeErrMsj = sprintf(&Package[4], error_msg);

	sizePackage = sizeErrMsj + 4;

	return true;
}

