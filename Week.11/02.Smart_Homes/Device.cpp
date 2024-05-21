#include "Device.h"
#pragma warning(disable : 4996)

void Device::free()
{
	delete[] name;
	delete[] manufacturer;

	name = nullptr;
	manufacturer = nullptr;
}

void Device::copyFrom(const Device& other)
{
	name = new char[std::strlen(other.name) + 1];
	std::strcpy(name, other.name);

	manufacturer = new char[std::strlen(other.manufacturer) + 1];
	std::strcpy(manufacturer, other.manufacturer);
}

void Device::moveFrom(Device&& other)
{
	name = other.name;
	other.name = nullptr;

	manufacturer = other.manufacturer;
	other.manufacturer = nullptr;
}

Device::Device(const char* name, const char* manufacturer)
{
	this->name = new char[std::strlen(name) + 1];
	std::strcpy(this->name, name);

	this->manufacturer = new char[std::strlen(manufacturer) + 1];
	std::strcpy(this->manufacturer, manufacturer);
}

Device::Device(const Device& other)
{
	copyFrom(other);
}

Device::Device(Device&& other)
{
	moveFrom(std::move(other));
}

Device& Device::operator=(const Device& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

Device& Device::operator=(Device&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Device::~Device()
{
	free();
}

void Device::printDetails() const
{
	std::cout << "Device: " << name << std::endl;
	std::cout << "Manufacturer: " << manufacturer << std::endl;
}

