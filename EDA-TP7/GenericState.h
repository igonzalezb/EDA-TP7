#ifndef GENERIC_STATE_H
#define GENERIC_STATE_H

/*	
*************************************************************************************************

	Estado genérico para una máquina de estados finitos que implementa una conexion TFTP.
	Para el caso de client, basta no redefinir las funciones onRrq() y onWrq().
	Para adaptar este estado genérico a una máquina de estados cualquiera, hacer las funciones
con el mismo formato que estas pero para los eventos que se quieran utilizar.

*/


#include <cstdio>
#include "GenericEvent.h"


class GenericState
{
public:	//reaction routines por default para cada evento
	virtual GenericState* onRrq (GenericEvent * ev) {return NULL;};
    virtual GenericState* onWrq (GenericEvent * ev) {return NULL;};
    virtual GenericState* onData (GenericEvent * ev) {return NULL;};
    virtual GenericState* onLastData (GenericEvent * ev) {return NULL;};
    virtual GenericState* onAck(GenericEvent * ev) {return NULL;};
    virtual GenericState* onLastAck (GenericEvent * ev) {return NULL;};
    virtual GenericState* onTimeout(GenericEvent * ev) {return NULL;};
    virtual GenericState* onError (GenericEvent * ev) {return NULL;};
    virtual GenericState* onExit (GenericEvent * ev) {return NULL;};
	

};


#endif // GENERIC_STATE_H
