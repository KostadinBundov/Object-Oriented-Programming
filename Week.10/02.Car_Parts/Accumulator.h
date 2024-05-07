#pragma once
#include "CarPart.h"

class Accumulator : public CarPart
{
private:
	unsigned _capacity = 0;
	char* _accumulatorId = nullptr;

	void free();
	void copyFrom(const Accumulator& other);
	void moveFrom(Accumulator&& other);

public:
	Accumulator(int id, const char* manufacturer, const char* description, unsigned capacity, const char* accumulatorId);
	Accumulator(const Accumulator& other);
	Accumulator(Accumulator&& other);
	Accumulator() = default;

	Accumulator& operator=(const Accumulator& other);
	Accumulator& operator=(Accumulator&& other);

	~Accumulator();

	unsigned getCapacity() const;
	const char* getAccumulatorId() const;

	void printInfo() const override;
};