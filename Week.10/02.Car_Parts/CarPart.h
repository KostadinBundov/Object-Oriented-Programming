#pragma once
#include <iostream>

class CarPart
{
private:
	int _id = -1;
	char* _manufacturer = nullptr;
	char* _description = nullptr;

	void free();
	void copyFrom(const CarPart& other);
	void moveFrom(CarPart&& other);

	void setId(int id);

public:
	CarPart() = default;
	CarPart(int id, const char* manufacturer, const char* description);

	CarPart(const CarPart& other);
	CarPart(CarPart&& other);

	CarPart& operator=(const CarPart& other);
	CarPart& operator=(CarPart&& other);

	virtual ~CarPart();

	 int getId() const;
	 const char* getManufacturer() const;
	 const char* getDescription() const;

	virtual void printInfo() const;
};