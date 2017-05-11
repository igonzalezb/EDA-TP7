#pragma once

#include <stdio.h>
#include <stdlib.h>

#define PackageSize 600
#define MaxSizeDATA 512

enum typePacket { _RRQ_ = 1, _WRQ_, _DATA_, _ACK_, _ERROR_,_LASTDATA_};

class PackageMaker
{
public:

	PackageMaker();

	bool makeACK(char* Package, unsigned int& sizePAcket);
	bool makeERROR(char* Package, unsigned int error_code, char* error_msg, unsigned int& sizePackage);
	bool makeDATA(char* Package, char* data, unsigned int sizeData, unsigned int& sizePackage);
	bool makeRRQ(char * Package, char* NombreTXT, unsigned int& sizePackage);
	bool makeWRQ(char * Package, char* NombreTXT, unsigned int& sizePackage);

	void setBlockNumber(int number);
	int getBlockNumber();
	void incBlockNumber();

	typePacket getTypePackage(char* Package, unsigned int sizePackage);

	bool decodeDATA(char* DATA, char* DATApackage, unsigned int sizeDATApackage, unsigned int& sizeDATA);

private:

	int BlockNumber;
};