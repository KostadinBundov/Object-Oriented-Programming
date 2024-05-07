#include "CarPart.h"
#pragma warning(disable : 4996)

void CarPart::free()
{
	delete[] _manufacturer;
	delete[] _description;
	
	_id = 0;
	_manufacturer = nullptr;
	_description = nullptr;
}

void CarPart::copyFrom(const CarPart& other)
{
	_id = other._id;

	_manufacturer = new char[std::strlen(other._manufacturer) + 1];
	std::strcpy(_manufacturer, other._manufacturer);

	_description = new char[std::strlen(other._description) + 1];
	std::strcpy(_description, other._description);
}

void CarPart::moveFrom(CarPart&& other)
{
	_id = other._id;
	_manufacturer = other._manufacturer;
	_description = other._description;

	other._id = 0;
	other._manufacturer = nullptr;
	other._description = nullptr;
}

void CarPart::setId(int id)
{
	if (id < 0)
	{
		throw std::invalid_argument("Id must be a positive number!");
	}

	_id = id;
}

CarPart::CarPart(int id, const char* manufacturer, const char* description)
{
	setId(id);

	if (!manufacturer || !description)
	{
		throw std::invalid_argument("Either manufacturer or description is empty");
	}

	_manufacturer = new char[std::strlen(manufacturer) + 1];
	std::strcpy(_manufacturer, manufacturer);

	_description = new char[std::strlen(description) + 1];
	std::strcpy(_description, description);
}

CarPart::CarPart(const CarPart& other)
{
	copyFrom(other);
}

CarPart::CarPart(CarPart&& other)
{
	moveFrom(std::move(other));
}

CarPart& CarPart::operator=(const CarPart& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

CarPart& CarPart::operator=(CarPart&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

CarPart::~CarPart()
{
	free();
}

int CarPart::getId() const
{
	return _id;
}

const char* CarPart::getManufacturer() const
{
	return _manufacturer;
}

const char* CarPart::getDescription() const
{
	return _description;
}

void CarPart::printInfo() const
{
	std::cout << "Part id: " << _id << std::endl;
	std::cout << "Manufacturer: " << _manufacturer << std::endl;
	std::cout << "Description: " << _description << std::endl;
}