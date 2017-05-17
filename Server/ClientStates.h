/*	
*************************************************************************************************

	Estados correspondientes al cliente en una conexión TFTP implementada con una FSM

*/

#ifndef CLIENT_STATES_H
#define CLIENT_STATES_H

#include "GenericState.h"
#include "GenericEvent.h"
#include "TPTF_FSM.h"


using namespace std;


class Reading : public GenericState
//Reading: recibiendo paquetes de datos del servidor
{
public:
    Reading() : GenericState (){};
    
    virtual GenericState* onData (GenericEvent * ev);
    virtual GenericState* onLastData (GenericEvent * ev);
    virtual GenericState* onTimeout(GenericEvent * ev);
    virtual GenericState* onError (GenericEvent * ev);
    virtual GenericState* onExit (GenericEvent * ev);
};


class Writing : public GenericState
{//enviando paquetes de datos al servidor
public:
    Writing() : GenericState (){};
    
    virtual GenericState* onAck(GenericEvent * ev);
    virtual GenericState* onLastAck (GenericEvent * ev);
    virtual GenericState* onTimeout(GenericEvent * ev);
    virtual GenericState* onError (GenericEvent * ev);
    virtual GenericState* onExit (GenericEvent * ev);   
};
#endif // CLIENT_STATES_H
