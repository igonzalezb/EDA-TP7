#ifndef TPTF_EVENTS_H
#define TPTF_EVENTS_H

/*	
*************************************************************************************************

	Eventos que pueden recibirse al simular una conexión TFTP, para cliente o servidor

*/


#define	CLIENT	1	
#define SERVER	0

#define I_AM	SERVER

#include "GenericEvent.h"
#include "usefulinfo.h"

using namespace std;


#if I_AM == CLIENT
enum eventos{ACK, LAST_ACK, DATA, LAST_DATA, TIMEOUT, _ERROR, EXIT};
#else
enum eventos{ACK, LAST_ACK, DATA, LAST_DATA, TIMEOUT, _ERROR, EXIT, RRQ, WRQ};

class Rrq: public GenericEvent	//READ REQUEST
{
public:
	Rrq(int size);
	~Rrq();
	char * getPackage(int * sizePackage);
	
private:
	char * Package;
	int size;


};

class Wrq: public GenericEvent	//WRITE REQUEST
{
public:
	Wrq(int size);
	~Wrq();
	char * getPackage(int * sizePackage);
	
private:
	char * Package;
	int size;
};

#endif

class Data: public GenericEvent		//RECIBIR UN PAQUETE DE DATOS
{
public:
	Data(int size);
	~Data();
	char * getPackage(int * sizePackage);
	
private:
	char * Package;
	int size;
};

class LastData: public GenericEvent	//RECIBIR EL ULTIMO PAQUETE DE DATOS
{
public:
	LastData(int size);
	~LastData();
	char * getPackage(int * sizePackage);

private:
	char * Package;
	int size;
};


class Ack: public GenericEvent		//CONFIRMACION DE QUE SE RECIBIO EL PAQUETE DE DATOS
{
public:
	Ack(int size);
	~Ack();
	char * getPackage(int * sizePackage);

private:
	char * Package;
	int size;
};

class LastAck: public GenericEvent	//CONFIMACION DE QUE SE RECIBIO EL ULTIMO PAQUETE DE DATOS
{
public:
	LastAck(int size);
	~LastAck();
	char * getPackage(int * sizePackage);

private:
	char * Package;
	int size;
};

class Timeout: public GenericEvent	//PASO MAS DEL TIEMPO ADMITIDO ENTRE UN DATA/ACK Y EL ACK/DATA ENVIADO
{
public:
	Timeout () : GenericEvent (TIMEOUT){;}
};

class Error: public GenericEvent		
{
public:
	Error(int size);
	~Error();
	char * getPackage(int * sizePackage);

private:
	char * Package;
	int size;
};

class Exit: public GenericEvent
{
public:
	Exit () : GenericEvent (EXIT){;}
};


#endif // TPTF_EVENTS_H 
