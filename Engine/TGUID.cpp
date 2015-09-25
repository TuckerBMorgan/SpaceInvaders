#include "Guid.h"

int TGUID::GUIDCount = 0;
bool TGUID::operator==(TGUID other)
{
	return other.number == this->number;
}

TGUID* TGUID::CreateGUID()
{
	TGUID *d =  new TGUID();
	d->number = TGUID::GUIDCount;
	TGUID::GUIDCount++;
	return d;
}