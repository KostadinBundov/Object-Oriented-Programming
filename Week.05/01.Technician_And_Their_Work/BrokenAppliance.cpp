#include "BrokenAppliance.h";

BrokenAppliance::BrokenAppliance(ApplianceCategory category, double priceForRepair, bool isInWarranty)
{
	this->setCategory(category);
	this->setPriceForRepair(priceForRepair);
	this->setIsInWarranty(isInWarranty);
}

ApplianceCategory BrokenAppliance::getCategory() const
{
	return this->category;
}

double BrokenAppliance::getPriceForRepair() const
{
	return this->priceForRepair;
}

bool BrokenAppliance::getIsInWarranty() const
{
	return this->isInWarranty;
}

void BrokenAppliance::setCategory(ApplianceCategory category)
{
	this->category = category;
}
void BrokenAppliance::setPriceForRepair(double price)
{
	this->priceForRepair = price;
}
void BrokenAppliance::setIsInWarranty(bool isInWarranty)
{
	this->isInWarranty = isInWarranty;
}