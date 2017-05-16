#include "timeOut.h"

GenericEvent * TimeOut::HayEvento()
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

void TimeOut::ResetTimer()
{

	pastTime = t.elapsed();
}

TimeOut::TimeOut()
{
	count = 0;
	t.start();
	pastTime = t.elapsed();

}

TimeOut::~TimeOut()
{
}

