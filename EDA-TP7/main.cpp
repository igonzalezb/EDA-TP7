/*	
*************************************************************************************************

	Este programa permite simular un cliente o servidor en una conexión TFTP, en función de lo 
que indique la constante I_AM, definida en el archivo "TFTP_Events.h".

*/

#include <iostream>
#include <cstdio>
#include "TPTF_Events.h"
#include "TPTF_FSM.h"


#if I_AM == CLIENT
#include "ClientStates.h"

#elif I_AM == SERVER
#include "ServerStates.h"

#define WRQ_K		'w'	//eventos unicamente para server
#define	RRQ_K		'r'

#else	
#error	"This program must emulate either a CLIENT or a SERVER in a TFTP connection"
#endif

using namespace std;

GenericEvent * eventGenerator();


int main(void) 
{
	GenericEvent * newEv = NULL;
	string lastEvent;

#if I_AM == CLIENT	
	TPTF_FSM fsm;
	
	switch (key) { //inicializar la FSM con el estado que corresponda segun lo recibido
		case 'r':
			printf("Estado: Reading");
			fsm.setState(new Reading());
		break;

		case 'w':
			printf("Estado: Writing");
			fsm.setState(new Writing());
		break;
	}	
#else
	TPTF_FSM fsm(new Idle());
#endif
	do {
		delete newEv;
		newEv = eventGenerator();	//recibir input del teclado

		if (newEv != NULL) //si se recibio algo, mostrarlo y llamar al dispatcher
		{ 
			fsm.dispatch(*newEv);
		}
	}
#if I_AM == CLIENT //condiciones para salir del loop en cliente
	while (newEv == NULL || (newEv->getType() != EXIT && newEv->getType()!= ERROR && 
		((newEv->getType()!=LAST_DATA || key == 'w') && (newEv->getType()!=LAST_ACK || key == 'r'))) );
#else //en server: solo si se aprieta EXIT
	while (newEv == NULL || newEv->getType() != EXIT);
#endif
	delete newEv;
		
	return EXIT_SUCCESS;
}


GenericEvent * eventGenerator()
{
//	GenericEvent * ev = NULL;
//
//	int key = getch();
//	
//	switch(tolower(key)){
//		case ACK_K:
//			ev = new Ack(ACTION_X,ACTION_Y); 
//			break;
//
//		case LAST_ACK_K:
//			ev = new LastAck(ACTION_X,ACTION_Y); 
//			break;
//
//		case DATA_K: 
//			ev = new Data(ACTION_X,ACTION_Y); 
//			break;
//
//		case LAST_DATA_K: 
//			ev = new LastData(ACTION_X,ACTION_Y); 
//			break;
//
//		case TIMEOUT_K: 
//			ev = new Timeout(ACTION_X,ACTION_Y); 
//			break;
//
//		case ERROR_K: 
//			ev = new Error(ACTION_X,ACTION_Y); 
//			break;
//
//		case EXIT_K: 
//			ev = new Exit(ACTION_X,ACTION_Y); 
//			break;
//#if I_AM == SERVER
//		case RRQ_K:
//			ev = new Rrq(ACTION_X,ACTION_Y);
//			break;
//
//		case WRQ_K:
//			ev = new Wrq(ACTION_X,ACTION_Y);
//			break;
//#endif // I_AM == SERVER
//	}
//
//	return ev;
	return NULL;
}