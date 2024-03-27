#include "BrokenAppliance.h";

BrokenAppliance::BrokenAppliance(const Category& category, double priceForRepair, bool isInWarranty)
{
	this->setCategory(category.getCategory());
	this->setPriceForRepair(priceForRepair);
	this->setIsInWarranty(isInWarranty);
}

ApplianceCategory BrokenAppliance::getCategory() const
{
	return this->category.getCategory();
}

double BrokenAppliance::getPriceForRepair() const
{
	return this->priceForRepair;
}

bool BrokenAppliance::getIsInWarranty() const
{
	return this->isInWarranty;
}

void BrokenAppliance::setCategory(const Category& category)
{
	this->category.setCategory(category.getCategory());
}
void BrokenAppliance::setPriceForRepair(double price)
{
	this->priceForRepair = price;
}
void BrokenAppliance::setIsInWarranty(bool isInWarranty)
{
	this->isInWarranty = isInWarranty;
}