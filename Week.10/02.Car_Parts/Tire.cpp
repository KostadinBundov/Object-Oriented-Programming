#include "Tire.h"

void Tire::setWidth(unsigned value)
{
	if (value < 155 || value > 365)
	{
		throw std::invalid_argument("Tyre width is invalid!");
	}

	_width = value;
}

void Tire::setProfile(unsigned value)
{
	if (value < 30 || value > 80)
	{
		throw std::invalid_argument("Tyre profile is invalid!");
	}

	_profile = value;
}

void Tire::setDiameter(unsigned value)
{
	if (value < 13 || value > 21)
	{
		throw std::invalid_argument("Tyre diameter is invalid!");
	}

	_diameter = value;
}

Tire::Tire(int id, const char* manufacturer, const char* description,unsigned width, unsigned profile, unsigned diameter) : CarPart(id, manufacturer, description)
{
	setWidth(width);
	setProfile(profile);
	setDiameter(diameter);
}

unsigned Tire::getWidth() const
{
	return _width;
}

unsigned Tire::getProfile() const
{
	return _profile;
}

unsigned Tire::getDiameter() const
{
	return _diameter;
}

void Tire::printInfo() const
{
	CarPart::printInfo();
	std::cout << "Width: " << _width << std::endl;
	std::cout << "Profile: " << _profile << std::endl;
	std::cout << "Diameter: " << _diameter << std::endl;
}
