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

	//crea el paquete ACK con el numero de bloque correspondiente al DATA 
	//devuelve el paquete en Package y el size del paquete en sizePackage
	bool makeACK(char* Package, unsigned int& sizePackage);



	//crea el paquete ERROR con el numero  y msj de error que recibe
	//devuelve el paquete en Package y el size del paquete en sizePackage
	bool makeERROR(char* Package, unsigned int error_code, char* error_msg, unsigned int& sizePackage);


	//crea el paquete DATA con el arreglo de data recibido y su respectivo tamano
	//devuelve el paquete en Package y el size del paquete en sizePackage
	bool makeDATA(char* Package, char* data, unsigned int sizeData, unsigned int& sizePackage);

	//crea el paquete DATA con el arreglo de data recibido y su respectivo tamano
	//devuelve el paquete en Package y el size del paquete en sizePackage
	bool makeRRQ(char * Package, char* NombreTXT, unsigned int& sizePackage);


	//crea el paquete WRQ con el nombre del .txt recibido
	//devuelve el paquete en Package y el size del paquete en sizePackage
	bool makeWRQ(char * Package, char* NombreTXT, unsigned int& sizePackage);


	//manejo del numero de bloque
	void setBlockNumber(int number);
	int getBlockNumber();
	void incBlockNumber();

	//te devuelve el tipo de paquete y te distingue DATA de LASTDATA
	typePacket getTypePackage(char* Package, unsigned int sizePackage);


	//le mandas el Paquete DATA completo y te devuelve un puntero al ArregloDATA y ademas
	//en sizeDATA devuelve la cantidad de bytes
	bool decodeDATA(char* DATA, char* DATApackage, unsigned int sizeDATApackage, unsigned int& sizeDATA); 


private:

	int BlockNumber;
};