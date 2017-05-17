/*	
*************************************************************************************************

	Este programa permite simular un cliente o servidor en una conexión TFTP, en función de lo 
que indique la constante I_AM, definida en el archivo "TFTP_Events.h".

*/

#include <iostream>
#include <cstdio>
#include "TPTF_Events.h"
#include "TPTF_FSM.h"
#include "usefulinfo.h"
#include "evNetworking.h"
#include "servidor.h"
#include "cliente.h"
#include "eventGenerator.h"
#include "FileManager.h"
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




int main(int argc, char *argv[])
{
	GenericEvent * newEv = NULL;
	string lastEvent;
	TPTF_FSM * fsm;


#if I_AM == CLIENT	
	char buff[600];
	char comando[600];
	char path[700];
	unsigned int sizePackage = 0;

	
	cliente Client;
	
	if (argc != 2)//si no hay exactamente dos argumentos, entonces cierro el programa
	{
		exit (4);
	}
	Client.ConectToServer(argv[1], "69");
	evNetworking Net(&Client);
	usefulInfo Info(&Net);
	//inicializo el sistema de archivos
	do
	{
		scanf("%s", comando);//espero a que se ingrese wrq o rrq
		scanf("%s", path);//espero que se ingrese el path del archivo
		for (int i = 0; i < strlen(comando); i++)//paso el comando amayusculas
			comando[i] = toupper(comando[i]);
	} while (strcmp(comando, "PUT")|| strcmp(comando, "GET"));
	
	if (!strcmp(comando, "PUT"))
	{
		//abro archivo en modo LECTURA
		Info.File = new DataPacket(path, true);
		//armo el paquete WRQ
		Info.makerDecoder.makeWRQ(buff, path, sizePackage);
		fsm = new TPTF_FSM(new Writing);
	}
	else
	{
		//abro archivo en modo escritura
		Info.File = new DataPacket(path, false);
		//armo el paquete RRQ
		Info.makerDecoder.makeRRQ(buff, path, sizePackage);
		fsm = new TPTF_FSM(new Reading);
	}

	
	//envio el paquete al servidor
	Info.Net->SendData(buff, sizePackage);
	eventGenerator Eg(&Info);
#else
	servidor Server(69);
	Server.waitForCliente();
	evNetworking Net(&Server);
	usefulInfo Info(&Net);
	eventGenerator Eg(&Info);
	fsm = new TPTF_FSM(new Idle);
#endif
	
	do {
		delete newEv;
		Eg.generateEvents();
		newEv = Eg.getEvents();	//recibir input del buffer

		if (newEv != NULL) //si se recibio algo, mostrarlo y llamar al dispatcher
		{ 
			fsm->dispatch(*newEv);
		}
	}
#if I_AM == CLIENT //condiciones para salir del loop en cliente
	while (newEv == NULL || (newEv->getType() != EXIT && newEv->getType()!= _ERROR && 
		((newEv->getType()!=LAST_DATA ) && (newEv->getType()!=LAST_ACK ))) );
#else //en server: solo si se aprieta EXIT
	while (newEv == NULL || newEv->getType() != EXIT);
#endif
	delete newEv;
	delete fsm;
	Net.~evNetworking();
	return EXIT_SUCCESS;
}


