#include "GenericEvent.h"

GenericEvent::GenericEvent(int type)
{
	this->type = (uint32_t)type;
}

uint32_t GenericEvent::getType()
{
	return type;
}
