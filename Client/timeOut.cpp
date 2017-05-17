#include "timeOut.h"

GenericEvent * timeOut::HayEvento()
{

	boost::timer::cpu_times currentTime = t.elapsed();

	if ((currentTime.wall - pastTime.wall) > 1e9)
	{
		this->ResetTimer();
		return new Timeout;
	}
	else
	{
		return NULL;
	}

}

void timeOut::ResetTimer()
{

	pastTime = t.elapsed();
}

timeOut::timeOut()
{
	count = 0;
	t.start();
	pastTime = t.elapsed();

}

timeOut::~timeOut()
{
}

