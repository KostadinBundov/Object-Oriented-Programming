#include "SmartLight.h"

SmartLight::SmartLight(const char* name, const char* manufacturer, unsigned brightnessLevel) : Device(name, manufacturer)
{
	this->brightnessLevel = brightnessLevel;
}

SmartLight::SmartLight(const SmartLight& other) : Device(other)
{
	this->brightnessLevel = other.brightnessLevel;
}

SmartLight::SmartLight(SmartLight&& other) : Device(std::move(other))
{
	this->brightnessLevel = other.brightnessLevel;
	other.brightnessLevel = 0;
}

SmartLight& SmartLight::operator=(const SmartLight& other)
{
	if (this != &other)
	{
		Device::operator=(other);
		this->brightnessLevel = other.brightnessLevel;
	}

	return *this;
}

SmartLight& SmartLight::operator=(SmartLight&& other)
{

	if (this != &other)
	{
		Device::operator=(std::move(other));
		this->brightnessLevel = other.brightnessLevel;
		other.brightnessLevel = 0;
	}

	return *this;
}

void SmartLight::turnOff() const
{
	std::cout << "Turning off smart light " << name << "...." << std::endl;
}

void SmartLight::turnOn() const
{
	std::cout << "Turning on smart light " << name << "...." << std::endl;
}

void SmartLight::printDetails() const
{
	Device::printDetails();
	std::cout << "Brightness level: " << brightnessLevel << std::endl;
}

Device* SmartLight::clone() const
{
	return new SmartLight(*this);
}
