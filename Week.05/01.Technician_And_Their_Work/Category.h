#pragma once

enum class ApplianceCategory {
	Unknown,
	Phone,
	Laptop,
	TV,
	WashingMachine,
	Spotlight,
	Camera,
	AirConditioning
};

class Category
{
private:
	ApplianceCategory category = ApplianceCategory::Unknown;

public:
	Category() = default;
	Category(ApplianceCategory category);

	ApplianceCategory getCategory() const;
	void setCategory(ApplianceCategory category);
};