#include "SmartSpeaker.h"

SmartSpeaker::SmartSpeaker(const char* name, const char* manufacturer, unsigned volumeLevel) : Device(name, manufacturer)
{
	this->volumeLevel = volumeLevel;
}

SmartSpeaker::SmartSpeaker(const SmartSpeaker& other) : Device(other)
{
	this->volumeLevel = other.volumeLevel;
}

SmartSpeaker::SmartSpeaker(SmartSpeaker&& other) : Device(std::move(other))
{
	this->volumeLevel = other.volumeLevel;
	other.volumeLevel = 0;
}

SmartSpeaker& SmartSpeaker::operator=(const SmartSpeaker& other)
{
	if (this != &other)
	{
		Device::operator=(other);
		this->volumeLevel = other.volumeLevel;
	}

	return *this;
}

SmartSpeaker& SmartSpeaker::operator=(SmartSpeaker&& other)
{

	if (this != &other)
	{
		Device::operator=(std::move(other));
		this->volumeLevel = other.volumeLevel;
		other.volumeLevel = 0;
	}

	return *this;
}

void SmartSpeaker::turnOff() const
{
	std::cout << "Turning off smart light " << name << "...." << std::endl;
}

void SmartSpeaker::turnOn() const
{
	std::cout << "Turning on smart light " << name << "...." << std::endl;
}

void SmartSpeaker::printDetails() const
{
	Device::printDetails();
	std::cout << "Volume level: " << volumeLevel << std::endl;
}

Device* SmartSpeaker::clone() const
{
	return new SmartSpeaker(*this);
}