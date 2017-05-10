#include "ServerStates.h"
#include "TPTF_Events.h"

GenericState* Idle::onRrq(GenericEvent * event)
{
	 
	//"start connection with client, send first data block"

	return new Reading();
}

GenericState* Idle::onWrq(GenericEvent * event)
{
	 
	//"start connection with client"
	return new Writing();
}

GenericState* Idle::onExit(GenericEvent * event)
{
	 
	//"shut down"
	return NULL;
}


GenericState* Writing :: onData (GenericEvent * event)
{
     
    //"store data, send ACK"
    return NULL;
}

GenericState* Writing :: onLastData (GenericEvent * event)
{
     
    //"store data, send LAST_ACK, end connection"    
    return new Idle();
}

GenericState* Writing :: onTimeout(GenericEvent * event)
{
     
    //"resend ACK (only once per data block)"
    return NULL;
}

GenericState* Writing :: onError (GenericEvent * event)
{
     
    //"end connection"
    return new Idle();
}

GenericState* Writing :: onExit (GenericEvent * event)
{
     
    //"end connection and shut down"    
    return NULL;
}


GenericState* Reading :: onAck(GenericEvent * event)
{
     
    //"send data"
    return NULL;
}

GenericState* Reading :: onLastAck (GenericEvent * event)
{
     
   //"end connection");
    return new Idle();
}

GenericState* Reading :: onTimeout(GenericEvent * event)
{
     
   //"resend data (only once per data block)"
    return NULL;
}

GenericState* Reading :: onError (GenericEvent * event)
{
     
   //"end connection");
    return new Idle();
}

GenericState* Reading :: onExit (GenericEvent * event)
{
     
   //"end connection and shut down"
    return NULL;
}