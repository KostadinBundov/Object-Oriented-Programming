#include <iostream>
#include "CommisionEmployee.h"
#include "HourlyEmployee.h"

// This is my Factory - the only place in the program where we know the exact type of every employee
Employee* createEmployee(std::istream& is)
{
	char employeeType;
	is >> employeeType;

	Employee* newEmployee = nullptr;

	if (employeeType == 'h')
	{
		MyString name;
		is >> name;

		double salary;
		is >> salary;

		unsigned overTime;
		is >> overTime;

		newEmployee = new HourlyEmployee(name, salary, overTime);
	}
	else if (employeeType == 'c')
	{
		MyString name;
		is >> name;

		double salary;
		is >> salary;

		unsigned commision;
		is >> commision;

		newEmployee = new CommisionEmployee(name, salary, commision);
	}
	
	return newEmployee;
}

void sortEmployees(const Employee** employees, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		int minElementIndex = i;
		double minSalary = employees[minElementIndex]->calculateSalary();

		for (int j = i + 1; j < size - 1; j++)
		{
			double currSalary = employees[j]->calculateSalary();

			if (currSalary < minSalary)
			{
				minSalary = currSalary;
				minElementIndex = j;
			}
		}

		if (minElementIndex != i)
		{
			std::swap(employees[i], employees[minElementIndex]);
		}
	}
}

double findMinSalary(Employee** employees, size_t size)
{
	if (size == 0)
	{
		return -1;
	}

	double minSalary = INT_MAX;

	for (int i = 0; i < size; i++)
	{
		double salary = employees[i]->calculateSalary();

		if (salary < minSalary)
		{
			minSalary = salary;
		}
	}

	return minSalary;
}

const Employee* getEmployeeWithCurrentSalary(const Employee** employees, size_t size)
{
	double minDifferencne = INT_MAX;
	const Employee* searchedEmployee = nullptr;

	double averageSalary = 0;

	for (int i = 0; i < size; i++)
	{
		averageSalary += (*employees[i]).calculateSalary();
	}

	averageSalary /= size;

	for (int i = 0; i < size; i++)
	{
		double currDifference = abs(averageSalary - employees[i]->calculateSalary());

		if (currDifference < minDifferencne)
		{
			minDifferencne = currDifference;
			searchedEmployee = employees[i];
		}
	}

	return searchedEmployee;
}

int main() 
{
	Employee** employees = new Employee*[10];
	size_t numEmployees = 0;
	char cont = 'y';

	std::cout << "Enter employee data (type 'h' for hourly or 'c' for commission, followed by name, salary, and hours or commission).\n";
	std::cout << "Enter 'n' to finish entering data.\n";

	while (cont != 'n' && numEmployees < 10) {
		std::cout << "Add another employee (y/n)? ";
		std::cin >> cont;
		if (cont == 'n') break;

		std::cout << "Enter employee type, name, base salary, and either hours (for hourly) or commission (for commission): ";
		employees[numEmployees] = createEmployee(std::cin);
		numEmployees++;
	}

	std::cout << "\nSalaries before sorting:\n";
	for (size_t i = 0; i < numEmployees; i++) {
		std::cout << employees[i]->calculateSalary() << std::endl;
	}

	sortEmployees(const_cast<const Employee**>(employees), numEmployees);

	std::cout << "\nSalaries after sorting:\n";
	for (size_t i = 0; i < numEmployees; i++) {
		std::cout << employees[i]->calculateSalary() << std::endl;
	}

	double minSalary = findMinSalary(employees, numEmployees);
	std::cout << "\nMinimum Salary: " << minSalary << std::endl;

	const Employee* closestToAverage = getEmployeeWithCurrentSalary(const_cast<const Employee**>(employees), numEmployees);
	std::cout << "\nEmployee closest to average salary: " << closestToAverage->getName() << std::endl;


	// free dynamic memory I am using because of memory leak
	for (size_t i = 0; i < numEmployees; i++) 
	{
		delete employees[i];
	}
	delete[] employees;
}

// an example for input for testing the code using the console
/*y
h
John
15.50
5
y
c
Jane
3000
200
y
h
Mike
20.00
2
y
c
Lisa
2500
150
n*/