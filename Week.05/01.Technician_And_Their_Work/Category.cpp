#include "Category.h";

Category::Category(ApplianceCategory category)
{
	this->setCategory(category);
}

ApplianceCategory Category::getCategory() const
{
	return this->category;
}

void Category::setCategory(ApplianceCategory category)
{
	this->category = category;
}