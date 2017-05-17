
#ifndef SERVER_STATES_H
#define SERVER_STATES_H

/*	
*************************************************************************************************

	Estados correspondientes al servidor en una conexión TFTP implementada con una FSM

*/

#include "GenericState.h"
#include "GenericEvent.h"
#include "TPTF_FSM.h"







class Idle : public  GenericState
{
public:
    Idle () :  GenericState (){};
    
    virtual GenericState* onRrq (GenericEvent * ev);
    virtual GenericState* onWrq (GenericEvent * ev);
    virtual GenericState* onExit (GenericEvent * ev); 
};
 

class Writing : public GenericState
{
public:
    Writing() : GenericState (){};
    
    virtual GenericState* onData (GenericEvent * ev);
    virtual GenericState* onLastData (GenericEvent * ev);
    virtual GenericState* onTimeout(GenericEvent * ev);
    virtual GenericState* onError (GenericEvent * ev);
    virtual GenericState* onExit (GenericEvent * ev);
};


class Reading : public GenericState
{
public:
    Reading() : GenericState (){};
     
    virtual GenericState* onAck(GenericEvent * ev);
    virtual GenericState* onLastAck (GenericEvent * ev);
    virtual GenericState* onTimeout(GenericEvent * ev);
    virtual GenericState* onError (GenericEvent * ev);
    virtual GenericState* onExit (GenericEvent * ev);
};

#endif // SERVER_STATES_H
