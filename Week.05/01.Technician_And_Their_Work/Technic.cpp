#include "Technic.h";
#include <string.h>
#include "Category.h";
#pragma warning (disable : 4996) 


Technic::Technic(const char* name, const char* UCN, uint8_t categories, double salary, unsigned experience) : categories(categories)
{
	this->setName(name);
	this->setUCN(UCN);
	this->setCategory(categories);
}

const char* Technic::getName() const
{
	return this->name;
}
const char* Technic::getUCN() const
{
	return this->UCN;
}
double Technic::getSalary() const
{
	return this->salary;
}
unsigned Technic::getExperience() const
{
	return this->experience;
}

void Technic::setName(const char* name)
{
	if (strlen(name) > TECHNIC_NAME_MAX_LENGTH)
	{
		return;
	}

	strcpy(this->name, name);
}
void Technic::setUCN(const char* UCN)
{
	if (strlen(UCN) != 10)
	{
		return;
	}

	strcpy(this->UCN, UCN);
}
void Technic::setCategory(uint8_t categories)
{
	this->categories = categories;
}

bool Technic::canRepairAppliance(const BrokenAppliance& appliance) const
{
	return ((uint8_t)appliance.getCategory() & this->categories) == (uint8_t)appliance.getCategory();
}

void Technic::repairBrokenAppliance(const BrokenAppliance& appliance)
{
	if (appliance.getIsInWarranty())
	{
		this->salary += appliance.getPriceForRepair();
		this->experience++;
	}
}
