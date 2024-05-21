#include "HourlyEmployee.h"

HourlyEmployee::HourlyEmployee(const MyString& name, double salary, unsigned hours) : Employee(name, salary), overTime(hours) {}

double HourlyEmployee::calculateSalary() const
{
	return 40 * 4 * salary + salary * 0.5 * overTime;
}
