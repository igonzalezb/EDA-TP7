#include "ClientStates.h"
#include "TPTF_Events.h"



GenericState* Reading :: onData (GenericEvent * event)
{
	
	//"store data, send ACK"
	
	return NULL;
}

GenericState* Reading :: onLastData (GenericEvent * event)
{
	
	//"store data, send LAST ACK, end connection"
	return NULL;
}

GenericState* Reading :: onTimeout(GenericEvent * event)
{
	
	//"resend ACK (once per data block)"
	
	return NULL;
}

GenericState* Reading :: onError (GenericEvent * event)
{
	
	//"end connection and shutdown"
	return NULL;
}

GenericState* Reading :: onExit (GenericEvent * event)
{
	
	//"end connection and shut down"
	return NULL;
}


GenericState* Writing :: onAck(GenericEvent * event)
{
	
	//"send data"
	return NULL;
}

GenericState* Writing :: onLastAck (GenericEvent * event)
{
	
	//"end connection and shut down"
	return NULL;
}

GenericState* Writing :: onTimeout(GenericEvent * event)
{
	
	//"resend data (only once per data block)"
	
	return NULL;
}

GenericState* Writing :: onError (GenericEvent * event)
{
	
	//"end connection and shut down"
	return NULL;
}

GenericState* Writing :: onExit (GenericEvent * event)
{
	
	//"end connection and shut down"
	return NULL;
}
