#include "SmartThermostat.h"

void SmartThermostat::copyFrom(const SmartThermostat& other)
{
	this->currentTemperature = other.currentTemperature;
	this->wantedTemperature = other.wantedTemperature;
}

SmartThermostat::SmartThermostat(const char* name, const char* manufacturer, int currentTemperature, int wantedTemperature) : Device(name, manufacturer)
{
	this->currentTemperature = currentTemperature;
	this->wantedTemperature = wantedTemperature;
}

SmartThermostat::SmartThermostat(const SmartThermostat& other) : Device(other)
{
	copyFrom(other);
}

SmartThermostat::SmartThermostat(SmartThermostat&& other) : Device(std::move(other))
{
	this->currentTemperature = other.currentTemperature;
	other.currentTemperature = 0;

	this->wantedTemperature = other.wantedTemperature;
	other.wantedTemperature = 0;
}

SmartThermostat& SmartThermostat::operator=(const SmartThermostat& other)
{
	if (this != &other)
	{
		Device::operator=(other);
		copyFrom(other);
	}

	return *this;
}

SmartThermostat& SmartThermostat::operator=(SmartThermostat&& other)
{

	if (this != &other)
	{
		Device::operator=(std::move(other));
		copyFrom(other);
	}

	return *this;
}

void SmartThermostat::turnOff() const
{
	std::cout << "Turning off smart light " << name << "...." << std::endl;
}

void SmartThermostat::turnOn() const
{
	std::cout << "Turning on smart light " << name << "...." << std::endl;
}

void SmartThermostat::printDetails() const
{
	Device::printDetails();
	std::cout << "Wanted temperature: " << wantedTemperature << std::endl;
	std::cout << "Current temperature: " << currentTemperature << std::endl;
}

Device* SmartThermostat::clone() const
{
	return new SmartThermostat(*this);
}
