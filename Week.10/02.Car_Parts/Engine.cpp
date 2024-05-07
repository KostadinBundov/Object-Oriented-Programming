#include "Engine.h"

Engine::Engine(int id, const char* manufacturer, const char* description, unsigned horsePowers) : CarPart(id, manufacturer, description)
{
	_horsePowers = horsePowers;
}

unsigned Engine::getHorsePowers() const
{
	return _horsePowers;
}

void Engine::printInfo() const
{
	CarPart::printInfo();
	std::cout << "Horse powers: " << _horsePowers << std::endl;
}
