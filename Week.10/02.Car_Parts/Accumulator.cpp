#include "Accumulator.h"
#pragma warning(disable : 4996)


void Accumulator::free()
{
	delete[] _accumulatorId;
	_accumulatorId = nullptr;
	_capacity = 0;
}

void Accumulator::copyFrom(const Accumulator& other)
{
	_capacity = other._capacity;
	_accumulatorId = new char[std::strlen(other._accumulatorId) + 1];
	std::strcpy(_accumulatorId, other._accumulatorId);
}

void Accumulator::moveFrom(Accumulator&& other)
{
	_capacity = other._capacity;
	_accumulatorId = other._accumulatorId;

	other._capacity = 0;
	other._accumulatorId = nullptr;
}

Accumulator::Accumulator(int id, const char* manufacturer, const char* description, unsigned capacity, const char* accumulatorId) : CarPart(id, "manufacturer", description)
{
	if (!accumulatorId)
	{
		throw std::invalid_argument("Accumulator's id is invalid!");
	}

	_capacity = capacity;
	_accumulatorId = new char[std::strlen(accumulatorId) + 1];
	std::strcpy(_accumulatorId, accumulatorId);
}

Accumulator::Accumulator(const Accumulator& other) : CarPart(other)
{
	copyFrom(other);
}

Accumulator::Accumulator(Accumulator&& other) : CarPart(std::move(other))
{
	moveFrom(std::move(other));
}

Accumulator& Accumulator::operator=(const Accumulator& other)
{
	if (this != &other)
	{
		CarPart::operator=(other);
		free();
		copyFrom(other);
	}

	return *this;
}

Accumulator& Accumulator::operator=(Accumulator&& other)
{
	if (this != &other)
	{
		CarPart::operator=(other);
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Accumulator::~Accumulator()
{
	free();
}

unsigned Accumulator::getCapacity() const
{
	return _capacity;
}

const char* Accumulator::getAccumulatorId() const
{
	return _accumulatorId;
}

void Accumulator::printInfo() const
{
	CarPart::printInfo();
	std::cout << "Capacity: " << _capacity << std::endl;
	std::cout << "Accumulator id: " << _accumulatorId << std::endl;
}
