#include "Car.h"

Car::Car(const FuelTank& tank, const Engine& engine, const Tire* tires, Accumulator accumulator, double weight) : _engine(engine), _tank(tank), _accumulator(accumulator), _weight(weight)
{
	for (int i = 0; i < 4; i++)
	{
		_tires[i] = tires[i];
	}
}

void Car::drive(double kilometers)
{
	_tank.spendFuel(kilometers);
	_treveledKilometers += kilometers;
}

const FuelTank& Car::getFuelTank() const
{
	return _tank;
}

bool Car::hasEnoughFuel(double kilometers) const
{
	return kilometers * 1 <= _tank.getLeftOver();
}

Car* dragRace(Car* fstCar, Car* sndCar)
{
	if (!fstCar->hasEnoughFuel(0.4))
	{
		return sndCar;
	}
	else if (!sndCar->hasEnoughFuel(0.4))
	{
		return fstCar;
	}
	else if(!fstCar->hasEnoughFuel(0.4) && !sndCar->hasEnoughFuel(0.4))
	{
		return nullptr;
	}
	else
	{
		double fstDiff = fstCar->_engine.getHorsePowers() / fstCar->_weight;
		double sndDiff = sndCar->_engine.getHorsePowers() / sndCar->_weight;

		if (fstDiff > sndDiff)
		{
			return fstCar;
		}
		else if (fstDiff < sndDiff)
		{
			return sndCar;
		}
		else
		{
			return nullptr;
		}
	}
}
