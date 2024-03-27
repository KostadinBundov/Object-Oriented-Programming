#pragma once
#include "Category.h";
#include "BrokenAppliance.h";

const size_t TECHNIC_NAME_MAX_LENGTH = 32;
const size_t UCN_LENGTH = 10;

class Technic
{
private:
	char name[TECHNIC_NAME_MAX_LENGTH] = "Unknown";
	char UCN[UCN_LENGTH] = "Unknown";
	Category category;
	double salary = 0;
	unsigned experience = 0;

public:
	Technic() = default;	
	Technic(const char* name, const char* UCN, const Category category, double salary, unsigned experience); // pottential problem with reference for category

	const  char* getName() const;
	const char* getUCN() const;
	ApplianceCategory getCategory() const;
	double getSalary() const;
	unsigned getExperience() const;

	void setName(const char* name);
	void setUCN(const char* UCN);
	void setCategory(const Category& category);

	bool canRepairAppliance(const BrokenAppliance& appliance) const;
	void repairBrokenAppliance(const BrokenAppliance& appliance);
};