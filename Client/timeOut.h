#pragma once
#include "TPTF_Events.h"
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>

class timeOut
{
public:
	timeOut();
	GenericEvent * HayEvento();
	void ResetTimer();
	~timeOut();

private:

	boost::timer::cpu_timer t;

	boost::timer::cpu_times pastTime;

	int count;
};
