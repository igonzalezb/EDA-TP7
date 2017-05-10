#ifndef GENERIC_EVENT_H
#define GENERIC_EVENT_H

/*	
*************************************************************************************************

	Evento base para una GenericFsm.

*/

#include <cstdint>



class GenericEvent
{
public:
	GenericEvent(int type) {this->type = (uint32_t)type;};

	uint32_t getType() { return type; };

protected:
	uint32_t type;

};



#endif //GENERIC_EVENT_H