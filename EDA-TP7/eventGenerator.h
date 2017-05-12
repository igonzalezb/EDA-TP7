#pragma once
#include "usefulinfo.h"
#include "evNetworking.h"
#include "GenericEvent.h"
class eventGenerator
{
public:
	eventGenerator(usefulInfo * I, evNetworking * Net);
	void generateEvents();
	GenericEvent * getEvents();

private:
	usefulInfo * I;
	evNetworking * Net;
};


