#pragma once
#include "Category.h";
#include "BrokenAppliance.h";
#include <cstdint>

const size_t TECHNIC_NAME_MAX_LENGTH = 32;
const size_t UCN_LENGTH = 10 + 1;

class Technic
{
private:
	char name[TECHNIC_NAME_MAX_LENGTH] = "Unknown";
	char UCN[UCN_LENGTH] = "Unknown";
	uint8_t categories = 0;
	double salary = 0;
	unsigned experience = 0;

	void setCategory(uint8_t categories);

public:
	Technic() = default;
	Technic(const char* name, const char* UCN, uint8_t categories, double salary, unsigned experience);

	const  char* getName() const;
	const char* getUCN() const;
	double getSalary() const;
	unsigned getExperience() const;

	void setName(const char* name);
	void setUCN(const char* UCN);


	bool canRepairAppliance(const BrokenAppliance& appliance) const;
	void repairBrokenAppliance(const BrokenAppliance& appliance);
};
