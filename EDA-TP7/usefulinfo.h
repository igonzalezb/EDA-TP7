#pragma once
#include <boost\circular_buffer.hpp>
#include "GenericEvent.h"
class usefulInfo
{
public:
	usefulInfo();
	~usefulInfo();
	boost::circular_buffer <GenericEvent *> buff;
private:
	
};

