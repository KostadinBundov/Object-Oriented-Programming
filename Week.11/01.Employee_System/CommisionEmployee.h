#pragma once
#include "Employee.h"

class CommisionEmployee : public Employee
{
private:
	unsigned commision = 0;

public:
	CommisionEmployee(const MyString& name, double salary, unsigned commision);
	double calculateSalary() const override;
};