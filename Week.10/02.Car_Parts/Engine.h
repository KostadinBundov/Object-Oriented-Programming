#pragma once
#include "carPart.h"

class Engine : public CarPart
{
private:
	unsigned _horsePowers = 0;

public:
	Engine() = default;
	Engine(int id, const char* manufacturer, const char* description, unsigned horsePowers);
	unsigned getHorsePowers() const;

	void printInfo() const override;
};