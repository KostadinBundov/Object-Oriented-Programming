#pragma once
#include <iostream>

class Device
{
private:
	void free();
	void copyFrom(const Device& other);
	void moveFrom(Device&& other);

protected:
	char* name = nullptr;
	char* manufacturer = nullptr;

public:
	Device(const char* name, const char* manufacturer);

	Device(const Device& other);
	Device(Device&& other);

	Device& operator=(const Device& other);
	Device& operator=(Device&& other);

	virtual ~Device();

	virtual void turnOn() const = 0;
	virtual void turnOff() const = 0;
	virtual void printDetails() const = 0;

	virtual Device* clone() const = 0;
};