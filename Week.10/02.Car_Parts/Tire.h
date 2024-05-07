#pragma once
#include "CarPart.h"

class Tire : public CarPart
{
private:
	unsigned _width = 0;
	unsigned _profile = 0;
	unsigned _diameter = 0;

	void setWidth(unsigned value);
	void setProfile(unsigned value);
	void setDiameter(unsigned value);

public:
	Tire() = default;
	Tire(int id, const char* manufacturer, const char* description, unsigned width, unsigned profile, unsigned diameter);

	unsigned getWidth() const;
	unsigned getProfile() const;
	unsigned getDiameter() const;

	void printInfo() const override;
};