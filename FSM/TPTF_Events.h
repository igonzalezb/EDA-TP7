#ifndef TPTF_EVENTS_H
#define TPTF_EVENTS_H

/*	
*************************************************************************************************

	Eventos que pueden recibirse al simular una conexión TFTP, para cliente o servidor

*/


#define	CLIENT	1	
#define SERVER	0

#define I_AM	SERVER

#include "FSM_Simulation.h"


using namespace std;


#if I_AM == CLIENT
enum eventos{ACK, LAST_ACK, DATA, LAST_DATA, TIMEOUT, ERROR, EXIT};
#else
enum eventos{ACK, LAST_ACK, DATA, LAST_DATA, TIMEOUT, ERROR, EXIT, RRQ, WRQ};

class Rrq: public GenericEvent	//READ REQUEST
{
public:
	Rrq () :GenericEvent (RRQ){;}
};

class Wrq: public GenericEvent	//WRITE REQUEST
{
public:
	Wrq () : GenericEvent (WRQ){;}
};

#endif

class Data: public GenericEvent		//RECIBIR UN PAQUETE DE DATOS
{
public:
	Data () : GenericEvent (DATA){;}
};

class LastData: public GenericEvent	//RECIBIR EL ULTIMO PAQUETE DE DATOS
{
public:
	LastData () : GenericEvent (LAST_DATA){;}
};


class Ack: public GenericEvent		//CONFIRMACION DE QUE SE RECIBIO EL PAQUETE DE DATOS
{
public:
	Ack () : GenericEvent (ACK){;}
};

class LastAck: public GenericEvent	//CONFIMACION DE QUE SE RECIBIO EL ULTIMO PAQUETE DE DATOS
{
public:
	LastAck () : GenericEvent (LAST_ACK){;}
};

class Timeout: public GenericEvent	//PASO MAS DEL TIEMPO ADMITIDO ENTRE UN DATA/ACK Y EL ACK/DATA ENVIADO
{
public:
	Timeout () : GenericEvent (TIMEOUT){;}
};

class Error: public GenericEvent		
{
public:
	Error () : GenericEvent (ERROR){;}
};

class Exit: public GenericEvent
{
public:
	Exit () : GenericEvent (EXIT){;}
};


#endif // TPTF_EVENTS_H 
