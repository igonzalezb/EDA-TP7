#include "TPTF_Events.h"
#include "usefulinfo.h"

using namespace std;

#if I_AM == SERVER

Rrq::Rrq(int size) :GenericEvent(RRQ)
{
	this->size = size;
	Package = new char[this->size];
}

Rrq::~Rrq()
{
	delete[] Package;
}

char * Rrq::getPackage(int * sizePackage)
{
	*sizePackage = size;
	return Package;
}

Wrq::Wrq(int size) : GenericEvent(WRQ)
{
	this->size = size;
	Package = new char[this->size];

}

Wrq::~Wrq()
{
	delete[] Package;
}

char * Wrq::getPackage(int * sizePackage)
{
	*sizePackage = size;
	return Package;
}
#endif
Data::Data(int size) : GenericEvent(DATA)
{
	this->size = size;
	Package = new char[this->size];
}

Data::~Data()
{
	delete[] Package;
}

char * Data::getPackage(int * sizePackage)
{
	*sizePackage = size;
	return Package;
}

LastData::LastData(int size) : GenericEvent(LAST_DATA)
{
	this->size = size;
	Package = new char[this->size];
}

LastData::~LastData()
{
	delete[] Package;
}

char * LastData::getPackage(int * sizePackage)
{
	*sizePackage = size;
	return Package;
}

Ack::Ack(int size) : GenericEvent(ACK)
{
	this->size = size;
	Package = new char[this->size];
}

Ack::~Ack()
{
	delete[] Package;
}

char * Ack::getPackage(int * sizePackage)
{
	*sizePackage = size;
	return Package;
}

LastAck::LastAck(int size) : GenericEvent(LAST_ACK)
{
	this->size = size;
	Package = new char[this->size];
}

LastAck::~LastAck()
{
	delete[] Package;
}

char * LastAck::getPackage(int * sizePackage)
{
	*sizePackage = size;
	return Package;
}

Error::Error(int size) : GenericEvent(_ERROR)
{
	this->size = size;
	Package = new char[this->size];
}

Error::~Error()
{
	delete[] Package;
}

char * Error::getPackage(int * sizePackage)
{
	*sizePackage = size;
	return Package;
}
