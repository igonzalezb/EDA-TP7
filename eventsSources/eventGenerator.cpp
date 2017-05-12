#include "eventGenerator.h"

eventGenerator::eventGenerator(usefulInfo * I, evNetworking * Net)
{
	this->I = I;
	this->Net = Net;
}


void eventGenerator::generateEvents()
{
	GenericEvent * ev = NULL;
	if ((ev = (Net->hayEvento())) != NULL)
	{
		I->buff.push_back(ev);
	}
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
