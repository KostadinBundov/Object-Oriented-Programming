#pragma once
#include "Employee.h"

class HourlyEmployee : public Employee
{
private:
	unsigned overTime = 0;

public:
	HourlyEmployee(const MyString& name, double salary, unsigned hours);
	double calculateSalary()const override;
};