#include "Client.h";
#include <string.h>
#pragma warning (disable : 4996) 

Client::Client(const char* name, const BrokenAppliance& appliance)
{
	this->setName(name);
	this->setAppliance(appliance);
}

const char* Client::getName() const
{
	return this->name;
}
const BrokenAppliance& Client::getAppliance() const
{
	return this->appliance;
}

void Client::setName(const char* name)
{
	if (strlen(name) > APPLIANCE_NAME_MAX_LENGTH)
	{
		return;
	}

	strcpy(this->name, name);
}
void Client::setAppliance(const BrokenAppliance& appliance)
{
	this->appliance = appliance;
}