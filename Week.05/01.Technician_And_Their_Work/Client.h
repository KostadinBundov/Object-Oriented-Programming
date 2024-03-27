#pragma once
#include "BrokenAppliance.h";

const size_t APPLIANCE_NAME_MAX_LENGTH = 32;

class Client
{
private:
	char name[APPLIANCE_NAME_MAX_LENGTH] = "Unknown";
	BrokenAppliance appliance;

public:
	Client() = default;
	Client(const char* name, const BrokenAppliance& appliance);

	const char* getName() const;
	const BrokenAppliance& getAppliance() const; // not sure if reference is needed

	void setName(const char* name);
	void setAppliance(const BrokenAppliance& appliance);
};