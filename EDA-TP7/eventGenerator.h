#pragma once
#include "usefulinfo.h"

#include "GenericEvent.h"
class eventGenerator
{
public:
	eventGenerator(usefulInfo * I);
	void generateEvents();
	GenericEvent * getEvents();

private:
	usefulInfo * I;

};


