#pragma once
#include "Engine.h"
#include "Tire.h"
#include "Accumulator.h"
#include "FuelTank.h"

class Car
{
private:
	FuelTank _tank;
	Engine _engine;
	Tire _tires[4];
	Accumulator _accumulator;
	double _treveledKilometers = 0;
	double _weight = 0;

public:
	Car() = default;
	Car(const FuelTank& tank, const Engine& engine, const Tire* tires, Accumulator accumulator, double weight);

	void drive(double kilometers);
	const FuelTank& getFuelTank() const;

	bool hasEnoughFuel(double kilometers) const;

	friend Car* dragRace(Car* fstCar, Car* sndCar);
};