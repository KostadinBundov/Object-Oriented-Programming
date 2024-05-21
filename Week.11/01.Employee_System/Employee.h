#pragma once
#include <iostream>
#include "MyString.h"

class Employee
{
protected:
	MyString name;
	double salary;

public:
	Employee(const MyString& name, double salary);
	virtual ~Employee() = default;

	const MyString& getName() const;

	virtual double calculateSalary() const = 0;
	friend std::ostream& operator<<(std::ostream& os, const Employee& employee);
};