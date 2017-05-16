#pragma once
#include "TPTF_Events.h"
#include <boost/chrono.hpp>
#include <boost/timer/timer.hpp>

class TimeOut
{
public:
	TimeOut();
	GenericEvent * HayEvento();
	void ResetTimer();
	~TimeOut();

private:

	boost::timer::cpu_timer t;

	boost::timer::cpu_times pastTime;

	int count;
};
