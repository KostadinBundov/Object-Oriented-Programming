#include "Employee.h"

Employee::Employee(const MyString& name, double salary)
{
	this->name = name;
	this->salary = salary;
}

std::ostream& operator<<(std::ostream& os, const Employee& employee)
{
	 os << "Employee name: " << employee.name << std::endl;
	 os << "Salary: " << employee.salary << std::endl;

	 return os;
}

const MyString& Employee::getName() const
{
	return name;
}
