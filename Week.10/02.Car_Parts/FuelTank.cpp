#include "FuelTank.h"

class insufficient_fuel_error : public std::logic_error
{
public:
	insufficient_fuel_error(const char* message) : std::logic_error(message) {}
};

FuelTank::FuelTank(double capacity)
{
	_capacity = capacity;
	_quantity = capacity;
}

void FuelTank::spendFuel(double quantity)
{
	if (quantity > _quantity)
	{
		throw insufficient_fuel_error("Not enough fuel in the tank!");
	}
	
	_quantity-= quantity;
}

void FuelTank::addFuel(double quantity)
{
	_quantity = (_quantity + quantity > _capacity) ? _capacity : (_quantity + quantity);
}

double FuelTank::getCapacity() const
{
	return _capacity;
}

double FuelTank::getLeftOver() const
{
	return _quantity;
}
