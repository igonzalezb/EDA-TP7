#pragma once

/*	
*************************************************************************************************

	Evento base para una GenericFsm.

*/

#include <cstdint>
//#include "usefulinfo.h"


class GenericEvent
{
public:
	GenericEvent(int type);

	uint32_t getType();
	
protected:

	uint32_t type;
	
};



