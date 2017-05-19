#include "eventGenerator.h"
#include "TPTF_Events.h"
eventGenerator::eventGenerator(usefulInfo * I)
{
	this->I = I;
	
}


void eventGenerator::generateEvents()
{
	GenericEvent * ev = NULL;
	if ((ev = (I->Net->hayEvento())) != NULL)
	{
		
		if ((I->isLastAck == true) && (ev->getType() == ACK))
		{
			delete ev;
			ev = new LastAck(2);
		}
		ev->UInfo = (void *)I;
		I->buff.push_back(ev);
		I->Tout.ResetTimer();
	}

	if ((ev = I->Tout.HayEvento()) != NULL)
	{
		I->buff.push_back(ev);
	}

#if I_AM == CLIENT
	if (((ev = I->Kboard.Input()) != NULL))
	{
		I->buff.push_back(ev);
	}
#endif
}

GenericEvent * eventGenerator::getEvents()
{
	GenericEvent * ev = NULL;
	if (I->buff.empty())//si el buffer esta vacio devuelvo un NULL
	{
		ev= NULL;
	}
	else
	{
		ev = I->buff[0];//almaceno el primer elemento en ev
		I->buff.pop_front();//borro ese elemento del buffer

	}
	return ev;
}
