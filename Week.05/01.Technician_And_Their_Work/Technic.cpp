#include "Technic.h";
#include <string.h>
#pragma warning (disable : 4996) 


Technic::Technic(const char* name, const char* UCN, const Category category, double salary, unsigned experience) : category(category)
{
	this->setName(name);
	this->setUCN(UCN);
	this->setCategory(category);
}

const char* Technic::getName() const
{
	return this->name;
}
const char* Technic::getUCN() const
{
	return this->UCN;
}
ApplianceCategory Technic::getCategory() const
{
	return this->category.getCategory();
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
void Technic::setCategory(const Category& category)
{
	this->category.setCategory(category.getCategory());
}

bool Technic::canRepairAppliance(const BrokenAppliance& appliance) const
{
	return this->category.getCategory() == appliance.getCategory();
}

void Technic::repairBrokenAppliance(const BrokenAppliance& appliance)
{
	if (appliance.getIsInWarranty())
	{
		this->salary += appliance.getPriceForRepair();
		this->experience++;
	}
}