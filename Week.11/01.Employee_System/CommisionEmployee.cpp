#include "CommisionEmployee.h"

CommisionEmployee::CommisionEmployee(const MyString& name, double salary, unsigned commision) : Employee(name, salary), commision(commision) {}

double CommisionEmployee::calculateSalary() const
{
	return salary + salary * commision;
}
