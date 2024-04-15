#pragma once
#include "Category.h";

class BrokenAppliance
{
private:
	ApplianceCategory category;
	double priceForRepair = 0;
	bool isInWarranty = true;

public:
	BrokenAppliance() = default;
	BrokenAppliance(ApplianceCategory category, double priceForRepair, bool isInWarranty);

	ApplianceCategory getCategory() const;
	double getPriceForRepair() const;
	bool getIsInWarranty() const;

	void setCategory(const ApplianceCategory category);
	void setPriceForRepair(double priceForRepair);
	void setIsInWarranty(bool isInWarranty);
};