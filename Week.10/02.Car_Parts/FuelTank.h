#pragma once
#include <iostream>

class FuelTank
{
private:
	double _capacity = 40;
	double _quantity = 40;

public:
	FuelTank(double capacity);
	FuelTank() = default;
	
	void spendFuel(double quantity);
	void addFuel(double quantity);

	double getCapacity() const;
	double getLeftOver() const;
};