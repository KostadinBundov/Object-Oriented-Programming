#include "SmartHome.h"

void SmartHome::copyFrom(const SmartHome& other)
{
	for (int i = 0; i < capacity; i++)
	{
		if (other.devices[i] != nullptr)
		{
			devices[i] = other.devices[i]->clone();
		}
	}

	size = other.size;
}

void SmartHome::moveFrom(SmartHome&& other)
{
	for (int i = 0; i < capacity; i++)
	{
		if (other.devices[i] != nullptr)
		{
			devices[i] = other.devices[i];
			other.devices[i] = nullptr;
		}
	}
}

void SmartHome::free()
{
	for (int i = 0; i < capacity; i++)
	{
		delete devices[i];
		devices[i] = nullptr;
	}
}

SmartHome::SmartHome(const SmartHome& other)
{
	copyFrom(other);
}

SmartHome::SmartHome(SmartHome&& other)
{
	moveFrom(std::move(other));
}

SmartHome& SmartHome::operator=(const SmartHome& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

SmartHome& SmartHome::operator=(SmartHome&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

SmartHome::~SmartHome()
{
	free();
}

size_t SmartHome::getDevicesCount() const
{
	return size;
}

const Device* SmartHome::getDevice(size_t index) const
{
	if (index >= size)
	{
		throw std::invalid_argument("Can't find device");
	}

	return devices[index];
}

void SmartHome::addDevice(const Device& device)
{
	if (size >= capacity)
	{
		throw std::invalid_argument("Can't add more devices to your home!");
	}


	Device* temp = device.clone();
	addDevice(temp);
}

void SmartHome::addDevice(Device* device)
{
	if (size >= capacity)
	{
		throw std::invalid_argument("Can't add more devices to your home!");
	}
	
	devices[size] = device;
	device = nullptr;
	size++;
}

void SmartHome::removeDevice()
{
	if (size <= 0)
	{
		throw std::invalid_argument("No devices were found!");
	}

	delete devices[size - 1];
	devices[size - 1] = nullptr;
	size--;
}
