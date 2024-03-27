#pragma once
#include "Category.h";

class BrokenAppliance
{
private:
	Category category;
	double priceForRepair = 0;
	bool isInWarranty = true;

public:
	BrokenAppliance() = default;
	BrokenAppliance(const Category& category, double priceForRepair, bool isInWarranty);

	ApplianceCategory getCategory() const;
	double getPriceForRepair() const;
	bool getIsInWarranty() const;

	void setCategory(const Category& category);
	void setPriceForRepair(double priceForRepair);
	void setIsInWarranty(bool isInWarranty);
};