#pragma once
#include "PackageMaker.h"
#include <string>
#include <fstream>
#define MaxSizeDATA 512

class DataPacket
{
public:

	DataPacket(std::string name, bool isReadMode);
	~DataPacket();

	//leer de a 512 del archivo, arma el paquete DATA y lo guarda en Package. 
	//Devuelve el tamano del paquete en sizePackage
	bool ReadDATA(char * Package, unsigned int & sizePackage);

	//Recibe el paquete DATA y su tamano, lo decodifica y escribe DATA en el archivo
	bool SaveDATA(char * DATApackage, unsigned int sizeDATApackage);

private:

	unsigned int sizeDATA; 
	char DATA[MaxSizeDATA];


	std::fstream archivo;
	bool isReadMode;

	PackageMaker P;
};
